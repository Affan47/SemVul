SubWinTest(WINDOW *win)
{
    int w, h, sw, sh, bx, by;
    WINDOW *swin1, *swin2, *swin3;

    getmaxyx(win, h, w);
    getbegyx(win, by, bx);
    sw = w / 3;
    sh = h / 3;
    if ((swin1 = subwin(win, sh, sw, by + 3, bx + 5)) == NULL)
	return 1;
    if ((swin2 = subwin(win, sh, sw, by + 4, bx + 8)) == NULL)
	return 1;
    if ((swin3 = subwin(win, sh, sw, by + 5, bx + 11)) == NULL)
	return 1;

    set_colors(swin1, 8, COLOR_RED, COLOR_BLUE);
    werase(swin1);
    mvwaddstr(swin1, 0, 3, "Sub-window 1");
    wrefresh(swin1);

    set_colors(swin2, 9, COLOR_CYAN, COLOR_MAGENTA);
    werase(swin2);
    mvwaddstr(swin2, 0, 3, "Sub-window 2");
    wrefresh(swin2);

    set_colors(swin3, 10, COLOR_YELLOW, COLOR_GREEN);
    werase(swin3);
    mvwaddstr(swin3, 0, 3, "Sub-window 3");
    wrefresh(swin3);

    delwin(swin1);
    delwin(swin2);
    delwin(swin3);
    WaitForUser(win);
    return 0;
}
