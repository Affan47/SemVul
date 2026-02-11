xread(int fd, void *buf, size_t len) {
    char *p;
    for (p = (char*)buf; p < (char*)buf + len; ) {
        ssize_t l;
        l = read(fd, p, (char*)buf + len - p);
        if (l == -1 && errno != EINTR)
            return -1;
        else if (l == 0)
            return 0;
        else
            p += l;
    }
    return len;
}
