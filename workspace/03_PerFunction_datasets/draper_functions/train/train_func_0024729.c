security_socket_accept(struct socket *sock, struct socket *newsock)
{
	return call_int_hook(socket_accept, 0, sock, newsock);
}
