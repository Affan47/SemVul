download_add_push_proxy(const struct guid *guid,
	host_addr_t addr, uint16 port)
{
	struct dl_server *server;

	server = htable_lookup(dl_by_guid, guid);
	if (server == NULL)
		return;

	g_assert(dl_server_valid(server));

	add_proxy(server, addr, port);
}
