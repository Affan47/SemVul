_fd_write_setup(void **testdata, int do_unlink) {
    struct fd_struct *f;
    char *filename;

    filename = crut_aprintf("%s.%d", TEST_PREFIX, 0);
    f = open_fd_struct(filename, O_WRONLY | O_CREAT | O_EXCL, do_unlink);
    free(filename);

    *testdata = f;
    if (f == NULL) {
        return -1;
    } else {
        return 0;
    }
}
