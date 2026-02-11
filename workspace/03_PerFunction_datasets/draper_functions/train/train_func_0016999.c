download_found_server(const struct guid *guid,
	const host_addr_t addr, uint16 port)
{
	struct dl_server *server;

	if (guid_is_blank(guid))
		return;


	server = htable_lookup(dl_by_guid, guid);

	if (NULL == server) {


		if (guid_eq(guid, GNET_PROPERTY(servent_guid))) {
			gnet_stats_inc_general(GNR_OWN_GUID_COLLISIONS);

			if (GNET_PROPERTY(download_debug)) {
				g_warning("discovered that host %s bears our GUID!",
					host_addr_port_to_string(addr, port));
			}

			return;
		}

		if (host_is_valid(addr, port)) {
			struct dl_addr ipk;

			ipk.addr = addr;
			ipk.port = port;

			server = htable_lookup(dl_by_addr, &ipk);

			if (server && guid_is_blank(server->key->guid)) {
				struct dl_key *key = server->key;

				if (GNET_PROPERTY(download_debug)) {
					g_debug("discovered GUID %s is for host %s "
						"which had a blank GUID", guid_to_string(guid),
						host_addr_port_to_string(addr, port));
				}

				hikset_remove(dl_by_host, key);
				gnet_stats_inc_general(GNR_DISCOVERED_SERVER_GUID);
				atom_guid_change(&key->guid, guid);
				htable_insert(dl_by_guid, key->guid, server);
				hikset_insert_key(dl_by_host, &server->key);
			}
		} else {
			if (GNET_PROPERTY(download_debug)) {
				g_debug("discovered GUID %s is for (firewalled) host %s, "
					"but server is gone!",
					guid_to_string(guid), host_addr_port_to_string(addr, port));
			}
		}

		return;
	}

	g_assert(dl_server_valid(server));


	if (host_addr_equal(addr, server->key->addr) && port == server->key->port)
		return;

	if (GNET_PROPERTY(download_debug))
		g_debug("discovered GUID %s is for host %s [%s] (was %s [%s])",
			guid_to_string(guid), host_addr_port_to_string(addr, port),
			iso3166_country_cc(gip_country(addr)),
			host_addr_port_to_string2(server->key->addr, server->key->port),
			iso3166_country_cc(server->country));

	change_server_addr(server, addr, port);
}
