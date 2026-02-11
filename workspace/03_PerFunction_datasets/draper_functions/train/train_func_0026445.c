gfarm_connect_wait(int s, int timeout_seconds)
{
	fd_set wset;
	struct timeval timeout;
	int rv, error, save_errno;
	socklen_t error_size;

	for (;;) {
		FD_ZERO(&wset);
		FD_SET(s, &wset);
		timeout.tv_sec = timeout_seconds;
		timeout.tv_usec = 0;


		rv = select(s + 1, NULL, &wset, NULL, &timeout);
		if (rv == 0)
			return (gfarm_errno_to_error(ETIMEDOUT));
		if (rv < 0) {
			if (errno == EINTR)
				continue;
			save_errno = errno;
			gflog_debug(GFARM_MSG_1001458, "select() failed: %s",
				strerror(save_errno));
			return (gfarm_errno_to_error(save_errno));
		}
		break;
	}

	error_size = sizeof(error);
	rv = getsockopt(s, SOL_SOCKET, SO_ERROR, &error, &error_size);
	if (rv == -1) {
		save_errno = errno;
		gflog_debug(GFARM_MSG_1001459, "getsocket() failed: %s",
			strerror(save_errno));
		return (gfarm_errno_to_error(save_errno));
	}
	if (error != 0) {
		gflog_debug(GFARM_MSG_1001460,
			"error occurred at socket: %s",
			gfarm_error_string(gfarm_errno_to_error(error)));
		return (gfarm_errno_to_error(error));
	}
	return (GFARM_ERR_NO_ERROR);
}
