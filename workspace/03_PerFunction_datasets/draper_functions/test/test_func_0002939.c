download_got_push_proxies(const struct guid *guid,
	const gnet_host_vec_t *proxies)
{
	struct dl_server *server;
	int i;
	size_t added = 0;

	server = htable_lookup(dl_by_guid, guid);
	if (server == NULL)
		return;

	g_assert(dl_server_valid(server));

	for (i = gnet_host_vec_count(proxies) - 1; i >= 0; i--) {
		struct gnutella_host host;
		host_addr_t addr;
		uint16 port;

		host = gnet_host_vec_get(proxies, i);
		addr = gnet_host_get_addr(&host);
		port = gnet_host_get_port(&host);

		if (
			host_addr_equal(addr, server->key->addr) &&
			port == server->key->port
		)
			continue;

		if (add_proxy(server, addr, port))
			added++;
	}

	if (added > 0) {
		if (GNET_PROPERTY(download_debug)) {
			g_debug("PUSH found %zu new push prox%s in query hit "
				"for GUID %s at %s",
				added, 1 == added ? "y" : "ies",
				guid_hex_str(guid), server_host_info(server));
		}
		gnet_stats_inc_general(GNR_COLLECTED_PUSH_PROXIES);
		download_push_proxy_wakeup(server, TRUE, FALSE);
	}
}
