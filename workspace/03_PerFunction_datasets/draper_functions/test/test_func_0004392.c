readn(d, buf, nbytes, auth)
	int d;
	void *buf;
	size_t nbytes;
	struct authmethod_t *auth;
{
	const char *function = "readn()";
	ssize_t p;
	size_t left = nbytes;

	do {
		if ((p = socks_recvfrom(d, &((char *)buf)[nbytes - left], left, 0, NULL,
		NULL, auth)) == -1) {
#if SOCKS_SERVER
			if (errno == EINTR)
				continue;
#else
			if (errno == EAGAIN) {
				fd_set rset;

				FD_ZERO(&rset);
				FD_SET(d, &rset);
				if (select(d + 1, &rset, NULL, NULL, NULL) == -1)
					swarn("%s: select()", function);

				continue;
			}
#endif
			break;
		}
		else if (p == 0)
			break;
		left -= p;
	} while (left > 0);

	if (left == nbytes)
		return p;
	return nbytes - left;
}
