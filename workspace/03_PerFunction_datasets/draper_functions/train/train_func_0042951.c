rinoo_socket_class_tcp_read(t_socket *socket, void *buf, size_t count)
{
	ssize_t ret;

	if (rinoo_socket_waitio(socket) != 0) {
		return -1;
	}
	errno = 0;
	while ((ret = read(socket->node.fd, buf, count)) < 0) {
		if (errno != EAGAIN && errno != EWOULDBLOCK) {
			return -1;
		}
		if (rinoo_socket_waitin(socket) != 0) {
			return -1;
		}
		errno = 0;
	}
	if (ret <= 0) {
		return -1;
	}
	return ret;
}
