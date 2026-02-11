event_user_mode(IRC_SERVER_REC *server, const char *data)
{
	char *params, *nick, *mode;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 3, NULL, &nick, &mode);
	parse_user_mode(server, mode);

	g_free(params);
}
