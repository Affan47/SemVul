proxy_redirect_event(CLIENT_REC *client, const char *command,
				 int count, const char *arg, int remote)
{
	char *str;

	g_return_if_fail(client != NULL);

	str = g_strdup_printf("proxy %p", client);
	server_redirect_event(client->server, command, count,
			      arg, remote, NULL, "", str, NULL);
	g_free(str);
}
