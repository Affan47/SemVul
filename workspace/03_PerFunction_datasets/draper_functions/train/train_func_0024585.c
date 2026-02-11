inet_tryaccept(p_socket server, int family, p_socket client,
    p_timeout tm)
{
	socklen_t len;
	t_sockaddr_storage addr;
	if (family == PF_INET6) {
		len = sizeof(struct sockaddr_in6);
	} else {
		len = sizeof(struct sockaddr_in);
	}
	return socket_strerror(socket_accept(server, client, (SA *) &addr,
        &len, tm));
}
