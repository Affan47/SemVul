is_stdin_ready() {
    int status = 0;
    fd_set ready_fdset;
    FD_ZERO(&ready_fdset);
    FD_SET(fileno(stdin), &ready_fdset);
    status = handle_select(fileno(stdin) + 1, &ready_fdset, NULL, NULL);
    return status == 1;
}
