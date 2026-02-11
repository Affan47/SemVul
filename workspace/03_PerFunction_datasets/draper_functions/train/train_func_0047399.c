server_list_by_index(struct dl_server *server, enum dl_list idx)
{
	g_assert(dl_server_valid(server));
	g_assert((uint) idx < DL_LIST_SZ);

	if (!server->list[idx]) {
		server->list[idx] = list_new();
	}
	return server->list[idx];
}
