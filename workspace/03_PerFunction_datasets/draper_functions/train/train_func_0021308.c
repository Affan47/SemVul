event_banlist(IRC_SERVER_REC *server, const char *data)
{
	IRC_CHANNEL_REC *chanrec;
	char *params, *channel, *ban, *setby, *tims;
	time_t tim;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 5, NULL, &channel, &ban, &setby, &tims);
	chanrec = irc_channel_find(server, channel);
	if (chanrec != NULL) {
		tim = (time_t) atol(tims);
		banlist_add(chanrec, ban, setby, tim);
	}
	g_free(params);
}
