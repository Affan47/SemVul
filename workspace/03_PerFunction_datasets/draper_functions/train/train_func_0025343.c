getColumns(void) {
    struct winsize ws;

    if (ioctl(1, TIOCGWINSZ, &ws) == -1) return 80;
    return ws.ws_col;
}
