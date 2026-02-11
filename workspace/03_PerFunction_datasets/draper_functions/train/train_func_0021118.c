Continue(WINDOW *win)
{
    int y1 = getmaxy(win);
    int x1 = getmaxx(win);
    int y0 = y1 < 10 ? y1 : 10;
    int x0 = 1;
    chtype save;

    save = mvwinch(win, y0, x1 - 1);

    mvwaddstr(win, y0, x0, " Press any key to continue");
    wclrtoeol(win);
    getyx(win, y0, x0);

    mvwaddch(win, y0, x1 - 1, save);

    wmove(win, y0, x0);
    raw();
    wgetch(win);
}
