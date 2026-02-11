mywrite(int fd, char *wherefrom, size_t len, int timeout)
{
	ssize_t cnt=0;

	while(len>0)
	{
		ssize_t rc;
		struct timeval to;
		fd_set wfds;

		FD_ZERO(&wfds);
		FD_SET(fd, &wfds);

		to.tv_sec  = timeout / 1000;
		to.tv_usec = (timeout - (to.tv_sec * 1000)) * 1000;

		rc = select(fd + 1, NULL, &wfds, NULL, &to);
		if (rc == 0)
			return -2;
		else if (rc == -1)
		{
			if (errno == EINTR || errno == EAGAIN)
				continue;

			snprintf(last_error, sizeof last_error, "mywrite::select failed: %s\n", strerror(errno));
			return -1;
		}

		rc = write(fd, wherefrom, len);

		if (rc == -1)
		{
			if (errno != EINTR && errno != EAGAIN)
			{
				snprintf(last_error, sizeof last_error, "mywrite::write failed: %s\n", strerror(errno));
				return -1;
			}
		}
		else if (rc == 0)
		{
			break;
		}
		else
		{
			wherefrom += rc;
			len -= rc;
			cnt += rc;
		}
	}

	return cnt;
}
