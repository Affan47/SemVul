query_change_server(QUERY_REC *query, SERVER_REC *server)
{
	g_return_if_fail(IS_QUERY(query));

	if (query->server != NULL) {
		query->server->queries =
                        g_slist_remove(query->server->queries, query);
	}
	if (server != NULL)
                server->queries = g_slist_append(server->queries, query);

	query->server = server;
	signal_emit("query server changed", 1, query);
}
