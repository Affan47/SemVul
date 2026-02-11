http_bind(struct evhttp *myhttp, ev_uint16_t *pport, int ipv6)
{
	int port;
	struct evhttp_bound_socket *sock;

	if (ipv6)
		sock = evhttp_bind_socket_with_handle(myhttp, "::1", *pport);
	else
		sock = evhttp_bind_socket_with_handle(myhttp, "127.0.0.1", *pport);

	if (sock == NULL) {
		if (ipv6)
			return -1;
		else
			event_errx(1, "Could not start web server");
	}

	port = regress_get_socket_port(evhttp_bound_socket_get_fd(sock));
	if (port < 0)
		return -1;
	*pport = (ev_uint16_t) port;

	return 0;
}
