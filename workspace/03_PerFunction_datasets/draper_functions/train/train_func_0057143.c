moveTetromino(StcGame *game, int x, int y) {
    int i, j, hasFullRow, numFilledRows;


    if (checkCollision(game, x, y)) {

        if (y == 1) {


            if (game->fallingBlock.y <= 1) {
                game->isOver = 1;
            }
            else {


                for (i = 0; i < game->fallingBlock.size; ++i) {
                    for (j = 0; j < game->fallingBlock.size; ++j) {
                        if (game->fallingBlock.cells[i][j] != EMPTY_CELL) {
                            game->map[game->fallingBlock.x + i][game->fallingBlock.y + j]
                                    = game->fallingBlock.cells[i][j];
                        }
                    }
                }


                numFilledRows = 0;
                for (j = 1; j < BOARD_HEIGHT; ++j) {
                    hasFullRow = 1;
                    for (i = 0; i < BOARD_WIDTH; ++i) {
                        if (game->map[i][j] == EMPTY_CELL) {
                            hasFullRow = 0;
                            break;
                        }
                    }


                    if (hasFullRow) {
                        for (x = 0; x < BOARD_WIDTH; ++x) {
                            for (y = j; y > 0; --y) {
                                game->map[x][y] = game->map[x][y - 1];
                            }
                        }
                        numFilledRows++;
                    }
                }


                if (numFilledRows) {
                    onFilledRows(game, numFilledRows);
                }
                game->stats.totalPieces++;
                game->stats.pieces[game->fallingBlock.type]++;


                for (i = 0; i < TETROMINO_SIZE; ++i) {
                    for (j = 0; j < TETROMINO_SIZE; ++j) {
                        game->fallingBlock.cells[i][j] = game->nextBlock.cells[i][j];
                    }
                }
                game->fallingBlock.size = game->nextBlock.size;
                game->fallingBlock.type = game->nextBlock.type;


                game->fallingBlock.y = 0;
                game->fallingBlock.x = (BOARD_WIDTH - game->fallingBlock.size) / 2;


                setTetromino(rand() % TETROMINO_TYPES, &game->nextBlock);
            }
        }
    }
    else {

        game->fallingBlock.x += x;
        game->fallingBlock.y += y;
    }
    onTetrominoMoved(game);
}
