skytraq_waitchar(int fd, int timeout)
{
	struct pollfd	fds[1];
	int		ret;
	unsigned char	c;

	for (;;) {
		fds[0].fd = fd;
		fds[0].events = POLLIN;
		ret = poll(fds, 1, timeout);
		if (ret >= 1) {
			if (fds[0].revents & POLLIN) {
				ret = read(fd, &c, 1);
				if (ret == 1) {
					skytraq_dbg_char(1, c);
					return c;
				}
			}
		} else if (ret == 0)
			return -2;
		else {
			perror("poll");
			return -1;
		}
	}
}
