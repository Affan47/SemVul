socket_shutdown(void)
{
	while (sl_incoming) {
		struct gnutella_socket *s = sl_incoming->data;

		socket_check(s);
		socket_destroy(s, NULL);
	}

	if (s_tcp_listen != NULL)
		upnp_unmap_tcp(s_tcp_listen->local_port);
	if (s_udp_listen != NULL)
		upnp_unmap_udp(s_udp_listen->local_port);


	socket_disable(s_local_listen);
	socket_disable(s_tcp_listen);
	socket_disable(s_tcp_listen6);
	socket_disable(s_udp_listen);
	socket_disable(s_udp_listen6);

	socket_shutdowned = TRUE;
}
