interactive_shell(void)
{
    adb_thread_t thr;
    int fdi, fd;
    int *fds;

    fd = adb_connect("shell:");
    if(fd < 0) {
        fprintf(stderr,"error: %s\n", adb_error());
        return 1;
    }
    fdi = 0;

    fds = malloc(sizeof(int) * 2);
    fds[0] = fd;
    fds[1] = fdi;

#ifdef HAVE_TERMIO_H
    stdin_raw_init(fdi);
#endif
    adb_thread_create(&thr, stdin_read_thread, fds);
    read_and_dump(fd);
#ifdef HAVE_TERMIO_H
    stdin_raw_restore(fdi);
#endif
    return 0;
}
