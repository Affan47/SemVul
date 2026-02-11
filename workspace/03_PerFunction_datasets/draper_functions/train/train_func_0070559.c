board_init() {
    const char *tee = memchr(display, 'T', screen_width);
    if (tee == NULL) {
        errexit(' ', "Can't determine board width.");
    }
    info_col = tee - display;
    const char *spc = memchr(display, ' ', screen_width);
    if (spc[-1] == '7' && isalpha(spc[-2]))
        spc--;
    board_width = pmin(spc, tee-1) - display;
    if (board_width % 2 == 0) {
        errexit(2, "Invalid width of %d.5 chars.", board_width/2);
    }
    board_width = (board_width + 1) / 2;
    if (board_width <= 5) {
        errexit(board_width+1, "Board unreasonably thin.");
    }
    if (board_width > 80) {
        errexit(board_width, "Board unreasonably wide.");
    }
    for (int i = 1; i < screen_height; i++) {
        if (D(i, 0) == 'z') {
            board_height = i;
            break;
        }
    }
    if (board_height == 0) {
        errexit(' ', "Can't determine board height.");
    }
    if (board_height <= 5) {
        errexit(board_height+1, "Board unreasonably short.");
    }
    if (board_height > 50) {
        errexit(board_height, "Board unreasonably tall.");
    }
    if (D(board_height-1, 0) != '-' && D(board_height-1, 2) != '-') {
        errexit('L', "Can't find lower left corner of board.");
    }
    int fnum = get_frame_no();
    if (fnum != 1) {
        errexit('t', "Starting at frame %d instead of 1.", fnum);
    }

    find_airports();
    fprintf(logff, "Board is %d by %d and the info column is %d.\n",
        board_width, board_height, info_col);

    return true;
}
