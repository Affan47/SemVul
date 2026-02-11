closefd(int fd)
{
    int r;
    while(1) {
	r = close(fd);
	if (r >= 0) return r;
	if (errno != EINTR) return r;
    }
}
