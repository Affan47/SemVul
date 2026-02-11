evutil_socket_connect(evutil_socket_t *fd_ptr, struct sockaddr *sa, int socklen)
{
	int made_fd = 0;

	if (*fd_ptr < 0) {
		made_fd = 1;
		if ((*fd_ptr = socket(sa->sa_family, SOCK_STREAM, 0)) < 0)
			goto err;
		if (evutil_make_socket_nonblocking(*fd_ptr) < 0) {
			goto err;
		}
	}

	if (connect(*fd_ptr, sa, socklen) < 0) {
		int e = evutil_socket_geterror(*fd_ptr);
		if (EVUTIL_ERR_CONNECT_RETRIABLE(e))
			return 0;
		goto err;
	} else {
		return 1;
	}

err:
	if (made_fd) {
		EVUTIL_CLOSESOCKET(*fd_ptr);
		*fd_ptr = -1;
	}
	return -1;
}
