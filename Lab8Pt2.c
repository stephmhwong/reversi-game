/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * Steph Wong *
 *
 * Date: March 22 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>

/*Function: setBoard
 * --------------------
 * set up board for the player given n */
void setBoard(char board[][26], int n) {
    // fill array with 'U' for [n][n] 
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            board[i][j] = 'U';
    // fill in the center 4 pieces of array from above 'B' and 'W' for specific pieces
    // the four pieces will always be in the 4 center spaces of the board
    board[(n/2)-1][(n/2)-1] = 'W';
    board[(n/2)-1][n/2] = 'B';
    board[n/2][n/2] = 'W';
    board[n/2][(n/2)-1] = 'B';
}

/* Function:  printBoard 
 * Print the whole board to the terminal window. */
void printBoard(char board[][26], int n){
    // printing the headers a-z in first row according to n --- NOTE: 'a' = 97 for %c
    printf("  ");
    for (int i = 0; i < n; i++)
        printf("%c", 97 + i);
    printf("\n");
    
    // print the first column of following rows with alphabet letter and then row of array, use a loop to print the whole array row by row
    for (int i = 0; i < n; i ++){
        printf("%c ", 97 + i);
        for (int j = 0; j < n; j ++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

/* Function:  positionInBounds 
 * Checks whether the specified (row, col) lies within the board dimensions. */
bool positionInBounds(int n, int row, int col) {
    bool inBounds = (row < n && col < n)? true: false; // if the row number and column number are less than n then return true, else return false
    return inBounds;
}

/* Function:  checkLegalInDirection
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol. */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    // NOTE: deltaRow/Col have values of -1, 0 and 1, never both 0, ex deltaRow = 1, deltaCol = 0, searches south line
    // 2 parts: first part if piece colour is black, then if piece colour is white
    // BLACK PIECE:
    // going to check that the piece in given direction is only 'W' and eventually reaches 'U', if so break the loop (stop checking) and return true,
    // if at any time the checking sees 'B' return false or sees 'U' before 'W' also return false (check 'U' first?)
    if (colour == 'B')
        //start counting from i = 1, stop the loop if the (row, col) being checked is off the board i.e less than equal to 0 or more than n
        // will return true if the specified space is 'U' and all pieces in that direction are 'W' until stopped by a 'B' piece
        if (board[row][col] == 'U')
            for (int i = 1; (row + i * deltaRow) < n && (row + i * deltaRow) >= 0 && (col + i * deltaCol) < n && 
            (col + i * deltaCol) >=0 && board[row + i * deltaRow][col + i * deltaCol] == 'W'; i ++)
                if (board[row + (i + 1) * deltaRow][col + (i + 1) * deltaCol] == 'B')
                    return true;
    
    // WHITE PIECE:
    // Same logic as black piece but instead check for 'B'
    if (colour == 'W')
        // will return true if the specified space is 'U' and all pieces in that direction are 'B' until stopped by a 'W' piece
        if (board[row][col] == 'U')
            for (int i = 1; (row + i * deltaRow) < n && (row + i * deltaRow) >= 0 && (col + i * deltaCol) < n && 
            (col + i * deltaCol) >= 0 && board[row + i * deltaRow][col + i * deltaCol] == 'B'; i ++)
                if (board[row + (i + 1) * deltaRow][col + (i + 1) * deltaCol] == 'W')
                    return true;
                    
    return false; // all the legal moves have already been consided, anything else will be not legal
}

/* Function: CheckAgainLegalInDirection
 * This function is used in the case that there are more than one directions in which the move is valid for
 * Different than CheckLegalInDirection because the space is alreadu ocupied if legal in more than one direction */
bool checkAgainLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    // BLACK PIECE:
    // is only 'W' and eventually reaches 'U', if so break the loop (stop checking) and return true,
    // if at any time the checking sees 'B' return false or sees 'U' before 'W' also return false (check 'B' first?)
    if (colour == 'B')
        //start counting from i = 1, stop the loop if the (row, col) being checked is off the board 
        // will return true if the specified space is 'B' and all pieces in that direction are 'W' until stopped by a 'B' piece
        if (board[row][col] == 'B')
            for (int i = 1; (row + i * deltaRow) < n && (row + i * deltaRow) >= 0 && (col + i * deltaCol) < n && 
            (col + i * deltaCol) >=0 && board[row + i * deltaRow][col + i * deltaCol] == 'W'; i ++)
                if (board[row + (i + 1) * deltaRow][col + (i + 1) * deltaCol] == 'B')
                    return true;
    
    // WHITE PIECE:
    // Same logic as black piece but instead check for 'B'
    if (colour == 'W')
        // will return true if the specified space is 'W' and all pieces in that direction are 'B' until stopped by another 'W' piece
        if (board[row][col] == 'W')
            for (int i = 1; (row + i * deltaRow) < n && (row + i * deltaRow) >= 0 && (col + i * deltaCol) < n && 
            (col + i * deltaCol) >= 0 && board[row + i * deltaRow][col + i * deltaCol] == 'B'; i ++)
                if (board[row + (i + 1) * deltaRow][col + (i + 1) * deltaCol] == 'W')
                    return true;
    
    return false; // all the legal moves have already been consided, anything else will be not legal            
}

/* Function: legalCheckAllDirection
 * this function will check for legality in all directions and return which direction it is legal for */ 
bool legalCheckAllDirections(char board[][26], int n, int row, int col, char colour){
    // check all directions returning true if legal in any directions, returns false that mean not legal in any direction
    
    if (/* NORTH */ checkLegalInDirection(board, n, row, col, colour, -1, 0) == true || /* SOUTH */ checkLegalInDirection(board, n, row, col, colour, 1, 0) == true || 
    /* EAST */ checkLegalInDirection(board, n, row, col, colour, 0, 1) == true || /* WEST */ checkLegalInDirection(board, n, row, col, colour, 0, -1) == true || 
    /* NORTHEAST */ checkLegalInDirection(board, n, row, col, colour, -1, 1) == true || /* NORTHEST */ checkLegalInDirection(board, n, row, col, colour, -1, -1) == true ||
    /* SOUTHEAST */ checkLegalInDirection(board, n, row, col, colour, 1, 1) == true || /* SOUTHWEST */ checkLegalInDirection(board, n, row, col, colour, 1, -1) == true)
        return true;
    
    return false; // if legal in no direction return false
}

/* Function: flipPieceInDirection
 * this function will flip all the pieces in a specified direction using deltaRow and deltaCol, return nothing, only changing board */ 
void flipPieceInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    // make a temp variable to hold whatever is currently in the specified position, this is to account for the potential of having more than one direction being legal
    char temp = board[row][col]; 
    board[row][col] = 'U'; // assign 'U' to the position bc checkLegalInDirection checks for 'U' as a condition
    
    if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true) // if legal in direction, flip all the pieces on opp colour
        for (int i = 0; board[row + i * deltaRow][col + i * deltaCol] != colour; i ++) // when reached the same colour, break the loop 
            board[row + i * deltaRow][col + i * deltaCol] = colour;
    else
        board[row][col] = temp; // if not legal in that direction, the position goes back to it's initial value
}

/* Function: flipPiece
 * this function will flip the pieces on the board accodring to the move made in all directions*/
void flipPiece(char board [][26], int n, int row, int col, char colour){
    // flip pieces in all directions
    flipPieceInDirection(board, n, row, col, colour, -1, 0); // NORTH //
    flipPieceInDirection(board, n, row, col, colour, 1, 0); // SOUTH //
    flipPieceInDirection(board, n, row, col, colour, 0, 1); // EAST // 
    flipPieceInDirection(board, n, row, col, colour, 0, -1); // WEST // 
    flipPieceInDirection(board, n, row, col, colour, -1, 1); // NORTHEAST //
    flipPieceInDirection(board, n, row, col, colour, -1, -1); // NORTHWEST //
    flipPieceInDirection(board, n, row, col, colour, 1, 1); // SOUTHEAST //
    flipPieceInDirection(board, n, row, col, colour, 1, -1); // SOUTHWEST //
}

/* Function:  countPieces
 * this function will count the number of pieces of a specified colour */
int countPieces(const char board[][26], int n, char colour){
    // initialize a counter to count the number of pieces, increase counter by 1 for every space occupied by specified colour
    int count = 0;
    
    for (int i = 0; i < n; i++) // check each position in array using a loop starting from (0,0)/ aa
        for( int j = 0; j < n; j++)
            if (board[i][j] == colour)
                count ++;
        
    return count;
}

/* Function:  countvalidMoves
 * this function counts the amount of valid moves available for the player in question */
int countValidMoves(char board[][26], int n, char colour){
    // initialize counter to count number of valid moves 
    int validMoves = 0;
    
    for (int i = 0; i < n; i ++) // look for valid moves, increasing the counter every time there is a valid move, return validMoves
        for (int j = 0; j < n; j ++)
            if (legalCheckAllDirections(board, n, i, j, colour) == true)
                validMoves++;
                
    return validMoves;
}

/* Function: findScoreForDirection
 * this fuction finds the score of the a specified direction using deltaRow and deltaCol */
int findScoreForDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    int score = 0; // initialize counter to count the score
    
    if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true)
        for (int i = 1; board[row + i * deltaRow][col + i * deltaCol] != colour; i ++) // does not count current position
            score++; // count pieces after the specified position following the directions specified, start index at 1 
    
    return score;
}

/* Function: findScore
 * this function will find the score of the given position, returns the score (int) */
int findScore(char board[][26], int n, int row, int col, char colour){
    int score = 0; // initialize counter for the score
    
    if (legalCheckAllDirections(board, n, row, col, colour) == true)
        score++; // if legal in one direction, increase score by one to include the current position
    else
        return score; // if not legal in any direction, return score which is 0
    
    // find score in specified direction and add it to the score counter
    score = findScoreForDirection(board, n, row, col, colour, -1, 0); // NORTH // 
    score = score + findScoreForDirection(board, n, row, col, colour, 1, 0); // SOUTH //
    score = score + findScoreForDirection(board, n, row, col, colour, 0, 1); // EAST // check that space is unoccupied,
    score = score + findScoreForDirection(board, n, row, col, colour, 0, -1); // WEST // check that space is unoccupied,
    score = score + findScoreForDirection(board, n, row, col, colour, -1, 1); // NORTHEAST // check that space is unoccupied.
    score = score + findScoreForDirection(board, n , row, col, colour, -1, -1); // NORTHWEST // check that space is unoccupied,
    score = score + findScoreForDirection(board, n, row, col, colour, 1, 1); // SOUTHEAST// check that space is unoccupied,
    score = score + findScoreForDirection(board, n, row, col, colour, 1, -1); // SOUTHWEST // check that space is unoccupied,
    
    return score;
}

/* Function:  makeMove 
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move. */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    // read the board to check for the best move for the computer
    // start with aa, and work way through array, checking each move validity. if move is valid, find the score and save the number, compare each
    // score calculated after with the highest score. since starting with the lowest row and lowest column in score = highscore, dont change best position
    // initialize variable for score and highest score
    int score = 0;
    int highestScore = 0;
    int lowestScore = 26;
    
    int totalPiecesOnBoard = countPieces(board, n, 'B') + countPieces(board, n, 'W');
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            
            score = findScore(board, n, i, j, turn);
            // for the for the first half of the game, make moves with the least possible score, this is as it is beneficial to have less pieces in the 
            // beginnning and then for the rest of the game the possible scores will be higher than if the computer made moves only with the 
            // highest scores every time, check for first quarter and rest of game by counting the number pieces on the board
            if (totalPiecesOnBoard <= ((n*n)/2) && score < lowestScore && score > 0){
                lowestScore = score; // change the best position if the current position is not a corner or edge
                row[0] = i;
                col[0] = j;
            }
        
            // rest of game, more than n^2/4 pieces on board, look for highest number of pieces flipped
            if (totalPiecesOnBoard > ((n*n)/2) && score > highestScore){
                highestScore = score; // change the best position if the current position is not a corner or edge
                row[0] = i;
                col[0] = j;
            }
            // set score back to 0 so when the loop repeats, counting from 0
            score = 0;
        }
    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    
    char board[26][26]; // initialize board
    char inputs[2]; // string to get user input 
    int bestRow[1]; // also initialize arrays for best position
    int bestCol[1]; // for rows and columns
    
    int n; // number of rows/col
    printf("Enter the board dimension: "); // prompt user for number of rows/cols
    scanf("%d", &n);
    
    // prompt user for computer's colour pieces 'B' for black 'W' for white
    printf("Computer plays (B/W): ");
    scanf("%s", inputs); // note stored in inputs[0]
    
    setBoard(board, n); // set up board
    printBoard(board, n); // print board for player
    
    // declare counters for counting valid moves of computer and player
    int compValidMoves, playerValidMoves;
    bool endGame = false; // initialize a variable to differentiate end of loop
        
    // Black player moves first
    // Computer is black, player is white therefore first move goes to computer
    if (inputs[0] == 'B'){
        do {
            // computer goes first, check for valid moves
            compValidMoves = countValidMoves(board, n, 'B');
            
            // if only computer has no valid moves, player gets the move, if player has move, make the move
            if (compValidMoves == 0) 
                printf("B player has no valid move.\n");
            if (compValidMoves > 0){
                makeMove(board, n, 'B', bestRow, bestCol); // find the best move for the comuter, print the move, make the move and print the board
                printf("Computer places B at %c%c.\n", bestRow[0] + 97, bestCol[0] + 97); // convert position into char using ASCII for printing
                flipPiece(board, n, bestRow[0], bestCol[0], 'B');
                printBoard(board, n); 
            }
            
            // check for end of game, if board is full
            int totalPiecesOnBoard = countPieces(board, n, 'W') + countPieces(board, n, 'B');
            if (totalPiecesOnBoard >= (n*n)){
                endGame = true;
                break;
            }
            
            playerValidMoves = countValidMoves(board, n, 'W'); // board has changed, check for playervalidmoves again
            
            if (playerValidMoves == 0)
                printf("W player has no valid move.\n");
            if (playerValidMoves > 0){
                // prompt the user for inputs and store in string (initialize a string)
                char playerInput[3];
                printf("Enter move for colour W (RowCol): ");
                scanf("%s", playerInput);
                
                int row = playerInput[0] - 'a'; //change char input into int for rows and columns
                int col = playerInput[1] - 'a';
                
                // check if inputed move is valid, invalid move from player ends the game, computer wins
                if (positionInBounds(n, row, col) == false || legalCheckAllDirections(board, n, row, col, 'W') == false){
                    printf("Invalid move.\nB player wins.\n"); // game ends, print results
                    break; //end the game
                }
                // valid move from player, make the move, change the board and print the board
                if (positionInBounds(n, row, col) == true && legalCheckAllDirections(board, n, row, col, 'W') == true){
                    flipPiece(board, n, row, col, 'W');
                    printBoard(board, n);
                }
            
            // Look for valid moves for the computer and player to check for end of game and count total pieces on board
            compValidMoves = countValidMoves(board, n, 'B');
            playerValidMoves = countValidMoves(board, n, 'W');      
            totalPiecesOnBoard = countPieces(board, n, 'W') + countPieces(board, n, 'B');
            
            // check conditions for end of game 
            if (compValidMoves == 0 && playerValidMoves == 0) // both player and computer have no moves left
                endGame = true;
            if (totalPiecesOnBoard >= (n*n)) // board is full, board has n*n spaces
                endGame = true;
            }
            
        } while(endGame == false); // stop the game when endGame = true
    }
    
    // computer is white, player is black therefore prompt user for first move
    // use a loop to repeat moves, player, comp, alternating
    if (inputs[0] == 'W'){
        do {
            // player goes first, check for valid moves
            playerValidMoves = countValidMoves(board, n, 'B');
            
            if (playerValidMoves == 0)
                printf("B player has no valid move.\n");
            if (playerValidMoves > 0){
                // prompt the user for inputs and store in string (initialize a string)
                char playerInput[3];
                printf("Enter move for colour B (RowCol): ");
                scanf("%s", playerInput);
                
                //change char input into int for rows and columns
                int row = playerInput[0] - 'a';
                int col = playerInput[1] - 'a';
                
                // check if inputed move is valid
                // invalid move from player ends the game, computer wins
                if (positionInBounds(n, row, col) == false || legalCheckAllDirections(board, n, row, col, 'B') == false){
                    printf("Invalid move.\nW player wins.\n"); // print game results
                    break; // end game
                }
                // valid move from player, make the move, change the board and print the board
                if (positionInBounds(n, row, col) == true && legalCheckAllDirections(board, n, row, col, 'B') == true){
                    flipPiece(board, n, row, col, 'B');
                    printBoard(board, n);
                }
                    
            }
            
            // check for end of game, if board is full
            int totalPiecesOnBoard = countPieces(board, n, 'W') + countPieces(board, n, 'B');
            if (totalPiecesOnBoard >= (n*n)){
                endGame = true;
                break;
            }
            
            compValidMoves = countValidMoves(board, n, 'W'); // board has changed, check for compvalidmoves
            
            // if only computer has no valid moves, player gets the move, if player has move, make the move
            if (compValidMoves == 0) 
                printf("W player has no valid move.\n");
            if (compValidMoves > 0){
                // find the best move for the comuter, print the move, make the move and print the board
                makeMove(board, n, 'W', bestRow, bestCol);
                printf("Computer places W at %c%c.\n", bestRow[0] + 97, bestCol[0] + 97); // convert position into char for printing using ASCII
                flipPiece(board, n, bestRow[0], bestCol[0], 'W');
                printBoard(board, n); 
            }
            
            // Look for valid moves for the computer and player and count total pieces on board
            compValidMoves = countValidMoves(board, n, 'W');
            playerValidMoves = countValidMoves(board, n, 'B');     
            totalPiecesOnBoard = countPieces(board, n, 'W') + countPieces(board, n, 'B'); 
            
            // check conditions for end of game 
            if (compValidMoves == 0 && playerValidMoves == 0) // both player and computer have no moves left
                endGame = true;
            if (totalPiecesOnBoard >= (n*n)) // board is full, board has n*n spaces
                endGame = true;
                
        } while(endGame == false); // stop the game when endGame = true
    }
    
    // print game results
    // game results of invalid player move already included, include endGame == true in condition game ended not due to invalid input from player
    if (endGame == true && countPieces(board, n, 'B') == countPieces(board, n, 'W')) // tie, same number of black and white pieces
        printf("Draw!\n");
    if (endGame == true && countPieces(board, n, 'B') > countPieces(board, n, 'W')) // B wins, more black pieces than white pieces
        printf("B player wins.\n");
    if (endGame == true && countPieces(board, n, 'B') < countPieces(board, n, 'W')) // W wins, more white pieces than black pieces
        printf("W player wins.\n");
        
    return 0;
}
#endif // DO NOT DELETE THIS LINE