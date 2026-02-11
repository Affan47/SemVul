writeOut(int fd, const void *buf, size_t len, const char *msg)
{
    ssize_t ret;
    if ((ret = write(fd, buf, len)) != (ssize_t)len) {
        if (ret >= 0)
            errno = -ENOSPC;
        logError(msg);
    }
    if (close(fd) < 0)
        logError(msg);
}
