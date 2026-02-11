VTCP_connect(int s, const struct sockaddr_storage *name, socklen_t namelen,
    int msec)
{
	int i, k;
	socklen_t l;
	struct pollfd fds[1];

	assert(s >= 0);


	if (msec > 0)
		(void)VTCP_nonblocking(s);


	i = connect(s, (const void *)name, namelen);
	if (i == 0 || errno != EINPROGRESS)
		return (i);

	assert(msec > 0);

	fds[0].fd = s;
	fds[0].events = POLLWRNORM;
	fds[0].revents = 0;
	i = poll(fds, 1, msec);

	if (i == 0) {

		errno = ETIMEDOUT;
		return (-1);
	}


	l = sizeof k;
	AZ(getsockopt(s, SOL_SOCKET, SO_ERROR, &k, &l));


	errno = k;
	if (k)
		return (-1);

	(void)VTCP_blocking(s);
	return (0);
}
