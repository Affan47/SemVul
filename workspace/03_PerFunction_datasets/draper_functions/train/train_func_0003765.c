write_atomic(int fd)
{
    char buf[BUFLEN];
    int retval;

    (void)strncpy(buf, PIPEDATA, sizeof(PIPEDATA));

    CRUT_DEBUG("Writing to pipe");
    retval = write(fd, buf, BUFLEN);
    if (sigpiped) {
        retval = -1;
        CRUT_FAIL("SIGPIPE on write");
    }
    if (retval < 0) {
        perror("write_atomic");
    } else if (retval != BUFLEN) {
        CRUT_FAIL("Wrote wrong length to pipe %d", fd);
    } else if(retval == BUFLEN) {
        retval = 0;
    }

    return retval;
}
