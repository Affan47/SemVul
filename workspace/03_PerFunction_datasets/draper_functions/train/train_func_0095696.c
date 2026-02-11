isns_socket_get_local_addr(const isns_socket_t *sock,
		struct sockaddr_storage *addr)
{
	socklen_t	alen;

	if (sock->is_desc < 0)
		return 0;
	if (getsockname(sock->is_desc,
			(struct sockaddr *) addr, &alen) < 0) {
		isns_error("getsockname: %m\n");
		return 0;
	}

	return 1;
}
