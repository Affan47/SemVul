wgetch_wrap(WINDOW *win, int first_y)
{
    int last_y = getmaxy(win) - 1;
    int y = getcury(win) + 1;

    if (y >= last_y)
	y = first_y;
    wmove(win, y, 0);
    wclrtoeol(win);
}
