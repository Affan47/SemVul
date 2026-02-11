event_nick(IRC_SERVER_REC *server, const char *data,
		       const char *sender, const char *addr)
{
	char *params, *newnick;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 1, &newnick);


	signal_emit(g_strcasecmp(newnick, server->nick) == 0 ?
		    "message own_nick" : "message nick", 4,
		    server, newnick, sender, addr);

	g_free(params);
}
