temp_file(char *buf, int bufsize)
{
        char *tmp;
        int n, fd;

        tmp = getenv("TMPDIR");
        if (!tmp)
                tmp = TMPDIR;

        n = snprint(buf, bufsize, "%s/sam.%d.XXXXXXX", tmp, getuid());
        if (bufsize <= n)
                return -1;
        if ((fd = mkstemp(buf)) < 0)
                return -1;
        if (fcntl(fd, F_SETFD, fcntl(fd,F_GETFD,0) | FD_CLOEXEC) < 0)
                return -1;
        return fd;
}
