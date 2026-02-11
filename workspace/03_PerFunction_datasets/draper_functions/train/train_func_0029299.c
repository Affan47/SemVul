main(int argc, char *argv[])
{
    WINDOW *chrbox;
    WINDOW *strwin;

    setlocale(LC_ALL, "");

    if (argc < 2) {
	fprintf(stderr, "usage: %s file\n", argv[0]);
	return EXIT_FAILURE;
    }

    initscr();

    chrbox = derwin(stdscr, BASE_Y, COLS, 0, 0);
    box(chrbox, 0, 0);
    wnoutrefresh(chrbox);

    strwin = derwin(chrbox, 4, COLS - 2, 1, 1);

    test_getstr(1, argv, strwin);

    endwin();
    ExitProgram(EXIT_SUCCESS);
}
