sock_recvfrom(php_netstream_data_t *sock, char *buf, size_t buflen, int flags,
		char **textaddr, long *textaddrlen,
		struct sockaddr **addr, socklen_t *addrlen
		TSRMLS_DC)
{
	php_sockaddr_storage sa;
	socklen_t sl = sizeof(sa);
	int ret;
	int want_addr = textaddr || addr;

	if (want_addr) {
		ret = recvfrom(sock->socket, buf, buflen, flags, (struct sockaddr*)&sa, &sl);
		ret = (ret == SOCK_CONN_ERR) ? -1 : ret;
		php_network_populate_name_from_sockaddr((struct sockaddr*)&sa, sl,
			textaddr, textaddrlen, addr, addrlen TSRMLS_CC);
	} else {
		ret = recv(sock->socket, buf, buflen, flags);
		ret = (ret == SOCK_CONN_ERR) ? -1 : ret;
	}

	return ret;
}
