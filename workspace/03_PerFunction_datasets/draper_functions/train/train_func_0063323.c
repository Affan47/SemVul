download_connected(struct download *d)
{
	struct gnutella_socket *s;

	download_check(d);
	dl_server_valid(d->server);
	socket_check(d->socket);
	g_assert(!download_pipelining(d));

	d->server->last_connect = tm_time();
	s = d->socket;
	socket_nodelay(s, TRUE);


	if (d->flags & DL_F_DNS_LOOKUP) {
		if (!host_addr_equal(download_addr(d), s->addr)) {
			if (GNET_PROPERTY(download_debug)) {
				g_debug("DNS lookup revealed server %s moved to %s",
					server_host_info(d->server), host_addr_to_string(s->addr));
			}
			change_server_addr(d->server, s->addr, download_port(d));
		}
	}

	download_send_request(d);
}
