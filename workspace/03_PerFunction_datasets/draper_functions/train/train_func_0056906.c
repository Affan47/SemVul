event_invite(IRC_SERVER_REC *server, const char *data,
			 const char *nick, const char *addr)
{
	char *params, *channel;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 2, NULL, &channel);
	signal_emit("message invite", 4,
		    server, get_visible_target(server, channel), nick, addr);
	g_free(params);
}
