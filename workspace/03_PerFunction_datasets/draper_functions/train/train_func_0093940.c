nonblock_safe_read(int fd, void *buf, size_t count)
{
	struct pollfd pfd[1];
	ssize_t n;

	while (1) {
		n = safe_read(fd, buf, count);
		if (n >= 0 || errno != EAGAIN)
			return n;

		pfd[0].fd = fd;
		pfd[0].events = POLLIN;
		safe_poll(pfd, 1, -1);
	}
}
