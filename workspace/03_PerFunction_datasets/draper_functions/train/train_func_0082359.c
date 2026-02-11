setTetromino(int indexTetromino, StcTetromino *tetromino) {


    setMatrixCells(&tetromino->cells[0][0], TETROMINO_SIZE, TETROMINO_SIZE, EMPTY_CELL);


    tetromino->size = TETROMINO_SIZE - 1;


    switch (indexTetromino) {
    case TETROMINO_I:
        tetromino->cells[0][1] = COLOR_CYAN;
        tetromino->cells[1][1] = COLOR_CYAN;
        tetromino->cells[2][1] = COLOR_CYAN;
        tetromino->cells[3][1] = COLOR_CYAN;
        tetromino->size = TETROMINO_SIZE;
        break;
    case TETROMINO_O:
        tetromino->cells[0][0] = COLOR_YELLOW;
        tetromino->cells[0][1] = COLOR_YELLOW;
        tetromino->cells[1][0] = COLOR_YELLOW;
        tetromino->cells[1][1] = COLOR_YELLOW;
        tetromino->size = TETROMINO_SIZE - 2;
        break;
    case TETROMINO_T:
        tetromino->cells[0][1] = COLOR_PURPLE;
        tetromino->cells[1][0] = COLOR_PURPLE;
        tetromino->cells[1][1] = COLOR_PURPLE;
        tetromino->cells[2][1] = COLOR_PURPLE;
        break;
    case TETROMINO_S:
        tetromino->cells[0][1] = COLOR_GREEN;
        tetromino->cells[1][0] = COLOR_GREEN;
        tetromino->cells[1][1] = COLOR_GREEN;
        tetromino->cells[2][0] = COLOR_GREEN;
        break;
    case TETROMINO_Z:
        tetromino->cells[0][0] = COLOR_RED;
        tetromino->cells[1][0] = COLOR_RED;
        tetromino->cells[1][1] = COLOR_RED;
        tetromino->cells[2][1] = COLOR_RED;
        break;
    case TETROMINO_J:
        tetromino->cells[0][0] = COLOR_BLUE;
        tetromino->cells[0][1] = COLOR_BLUE;
        tetromino->cells[1][1] = COLOR_BLUE;
        tetromino->cells[2][1] = COLOR_BLUE;
        break;
    case TETROMINO_L:
        tetromino->cells[0][1] = COLOR_ORANGE;
        tetromino->cells[1][1] = COLOR_ORANGE;
        tetromino->cells[2][0] = COLOR_ORANGE;
        tetromino->cells[2][1] = COLOR_ORANGE;
        break;
    }
    tetromino->type = indexTetromino;
}
