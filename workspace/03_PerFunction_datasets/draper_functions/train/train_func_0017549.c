event_connected(IRC_SERVER_REC *server)
{
	const char *nick;

	g_return_if_fail(server != NULL);

        nick = server->connrec->nick;
	if (g_strcasecmp(server->nick, nick) == 0)
		return;


	server_redirect_event(server, "whois", 1, nick, TRUE, NULL,
			      "event 311", "nickfind event whois",
			      "", "event empty", NULL);
	irc_send_cmdv(server, "WHOIS %s", nick);
}
