destroy_server(struct server_data *server)
{
	GList *list;

	DBG("index %d server %s sock %d", server->index, server->server,
			server->channel != NULL ?
			g_io_channel_unix_get_fd(server->channel): -1);

	server_list = g_slist_remove(server_list, server);
	server_destroy_socket(server);

	if (server->protocol == IPPROTO_UDP && server->enabled)
		DBG("Removing DNS server %s", server->server);

	g_free(server->server);
	for (list = server->domains; list; list = list->next) {
		char *domain = list->data;

		server->domains = g_list_remove(server->domains, domain);
		g_free(domain);
	}
	g_free(server->server_addr);


	g_timeout_add_seconds(3, try_remove_cache, NULL);

	g_free(server);
}
