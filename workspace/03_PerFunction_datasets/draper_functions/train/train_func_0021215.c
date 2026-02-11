rinoo_socket_class_udp_bind(t_socket *socket, const struct sockaddr *addr, socklen_t addrlen, int unused(backlog))
{
	int enabled;

	enabled = 1;

#ifdef SO_REUSEPORT
	if (setsockopt(socket->node.fd, SOL_SOCKET, SO_REUSEPORT, &enabled, sizeof(enabled)) == -1) {
		return -1;
	}
#endif

	if (setsockopt(socket->node.fd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(enabled)) == -1 || bind(socket->node.fd, addr, addrlen) == -1) {
		return -1;
	}
	return 0;
}
