net_recv_ex(int sock, void *buf, int size, struct timeval *tv)
{

	fd_set	fds;
	int		res;


	do {
		errno = 0;
		FD_ZERO(&fds);
		FD_SET(sock, &fds);
		res = select(sock + 1, &fds, NULL, NULL, tv);
	} while (res < 0 && errno == EINTR);
	if (res < 0) return 0;
	if (res == 0) {

		errno = ETIMEDOUT;
		return 0;
	}


	do {
		errno = 0;
		res = recv(sock, (char*)buf, size, 0);
	} while (res < 0 && errno == EINTR);
	if (res < 0) return 0;
	if (res == 0) {

		errno = ENOTCONN;
		return 0;
	}

	return res;
}
