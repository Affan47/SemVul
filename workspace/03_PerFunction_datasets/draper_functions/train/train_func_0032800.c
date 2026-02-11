snarf_file(int fd)
{
    static char	*buf = 0;
    static long	 len = 0;
    struct stat	stat_buf;
    long	n;

    if (fstat(fd, &stat_buf) < 0) {
	perror("fstat");
	return 0;
    }
    n = stat_buf.st_size;
    if (len <= n)
	buf = xrealloc(buf, len = n + 1);

    n = read(fd, buf, n);
    if (n < 0) {
	perror("read");
	free(buf);
	return 0;
    }
    buf[n] = '\0';

    return buf;
}
