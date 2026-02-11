sock_sendto(php_netstream_data_t *sock, char *buf, size_t buflen, int flags,
		struct sockaddr *addr, socklen_t addrlen
		TSRMLS_DC)
{
	int ret;
	if (addr) {
		ret = sendto(sock->socket, buf, buflen, flags, addr, addrlen);
		return (ret == SOCK_CONN_ERR) ? -1 : ret;
	}
	return ((ret = send(sock->socket, buf, buflen, flags)) == SOCK_CONN_ERR) ? -1 : ret;
}
