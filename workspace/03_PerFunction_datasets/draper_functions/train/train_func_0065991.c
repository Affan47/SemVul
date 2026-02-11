fmap_check_empty(int fd, off_t offset, size_t len, int *empty) {
    unsigned int pages, mapsz, hdrsz;
    unsigned short dumb = 1;
    int pgsz = cli_getpagesize();
    STATBUF st;
    fmap_t *m;
    void *handle = (void*)(ssize_t)fd;

    *empty = 0;
    if(FSTAT(fd, &st)) {
	cli_warnmsg("fmap: fstat failed\n");
	return NULL;
    }

    if(!len) len = st.st_size - offset;
    if(!len) {
	cli_dbgmsg("fmap: attempted void mapping\n");
	*empty = 1;
	return NULL;
    }
    if(!CLI_ISCONTAINED(0, st.st_size, offset, len)) {
	cli_warnmsg("fmap: attempted oof mapping\n");
	return NULL;
    }
    m = cl_fmap_open_handle((void*)(ssize_t)fd, offset, len, pread_cb, 1);
    if (!m)
	return NULL;
    m->mtime = st.st_mtime;
    m->handle_is_fd = 1;
    return m;
}
