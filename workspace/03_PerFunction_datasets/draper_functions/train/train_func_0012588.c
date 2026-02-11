wiz_timeout_queue(void)
{
    winid win;
    char buf[BUFSZ];

    win = create_nhwindow(NHW_MENU);
    if (win == WIN_ERR) return 0;

    sprintf(buf, "Current time = %ld.", monstermoves);
    putstr(win, 0, buf);
    putstr(win, 0, "");
    putstr(win, 0, "Active timeout queue:");
    putstr(win, 0, "");
    print_queue(win, timer_base);

    display_nhwindow(win, false);
    destroy_nhwindow(win);

    return 0;
}
