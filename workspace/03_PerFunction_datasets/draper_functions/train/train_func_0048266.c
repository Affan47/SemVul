BouncingBalls(WINDOW *win)
{
    int w, h;
    int x1, y1, xd1, yd1;
    int x2, y2, xd2, yd2;
    int x3, y3, xd3, yd3;

    getmaxyx(win, h, w);

    x1 = 2 + rand() % (w - 4);
    y1 = 2 + rand() % (h - 4);
    x2 = 2 + rand() % (w - 4);
    y2 = 2 + rand() % (h - 4);
    x3 = 2 + rand() % (w - 4);
    y3 = 2 + rand() % (h - 4);

    xd1 = 1;
    yd1 = 1;
    xd2 = 1;
    yd2 = 0;
    xd3 = 0;
    yd3 = 1;

    nodelay(win, TRUE);

    while (wgetch(win) == ERR) {
	x1 = bounce(x1, &xd1, w);
	y1 = bounce(y1, &yd1, h);
	x2 = bounce(x2, &xd2, w);
	y2 = bounce(y2, &yd2, h);
	x3 = bounce(x3, &xd3, w);
	y3 = bounce(y3, &yd3, h);

	set_colors(win, 11, COLOR_RED, COLOR_BLUE);
	mvwaddch(win, y1, x1, 'O');

	set_colors(win, 12, COLOR_BLUE, COLOR_RED);
	mvwaddch(win, y2, x2, '*');

	set_colors(win, 13, COLOR_YELLOW, COLOR_WHITE);
	mvwaddch(win, y3, x3, '@');

	wmove(win, 0, 0);
	wrefresh(win);
	delay_output(100);
    }
    return 0;
}
