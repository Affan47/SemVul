timed_read(int fd, void *data, int datalen)
{
	int res;
	struct pollfd fds[1];
	fds[0].fd = fd;
	fds[0].events = POLLIN;
	res = ast_poll(fds, 1, 2000);
	if (res < 1) {
		ast_log(LOG_NOTICE, "Selected timed out/errored out with %d\n", res);
		return -1;
	}
	return read(fd, data, datalen);

}
