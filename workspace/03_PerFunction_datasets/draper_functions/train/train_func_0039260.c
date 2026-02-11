fd_write_restart(void *p)
{
    int retval;
    struct fd_struct *f = (struct fd_struct *)p;
    struct fd_struct *readf;
    char buf[BUF_SIZE];


    retval = check_flags(f);
    if (retval < 0) {
	goto out;
    }
    CRUT_DEBUG("check_flags:return = %d", retval);


    retval = check_offset(f);
    if (retval < 0) {
	goto out;
    }
    CRUT_DEBUG("check_offset:return = %d", retval);


    retval = check_stat_simple(f);
    if (retval < 0) {
	goto out;
    }
    CRUT_DEBUG("check_stat_simple:return = %d", retval);


    retval = write_pattern(f->fd, DEFAULT_TEST_DATA_LENGTH);
    if (retval < 0) {
        goto out;
    }
    CRUT_DEBUG("write_pattern:return = %d", retval);


    retval = read(f->fd, buf, sizeof(*f));
    if (retval >= 0) {
        perror("read");
        CRUT_FAIL("Unexpectedly able to read from a write-only file!");
    } else if (errno != EBADF) {
        CRUT_FAIL("Read failed, but for the wrong reason!");
        perror("read");
    } else {
        retval = 0;
    }


    if (f->unlinked) goto out;


    readf = open_fd_struct(f->filename, O_RDONLY, 0);
    if (readf == NULL) {
        retval = -1;
	goto out;
    }
    p = readf;


    retval = check_pattern(readf->fd, DEFAULT_TEST_DATA_LENGTH);
    if (retval < 0) {
        goto out;
    }

out:
    return retval;
}
