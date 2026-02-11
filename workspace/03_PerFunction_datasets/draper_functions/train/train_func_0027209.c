client_new(evutil_socket_t sock)
{
	struct client *client;

	client = mem_calloc(1, sizeof(*client));
	TAILQ_INIT(&client->requests);
	client->conn = http_conn_new(proxy_event_base, sock, HTTP_CLIENT,
				&client_methods, client);

	log_debug("proxy: new client %p", client);

	return client;
}
