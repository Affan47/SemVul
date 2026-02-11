fill_window(WINDOW *win)
{
    int y, x;

    getyx(win, y, x);
    wmove(win, 0, 0);
    while (waddstr(win, "0123456789 abcdefghijklmnopqrstuvwxyz ") != ERR) {
    }
    wmove(win, y, x);
}
