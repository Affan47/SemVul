sig_connected(XMPP_SERVER_REC *server)
{
	if (!IS_XMPP_SERVER(server) || !server->connrec->reconnection)
		return;
	signal_emit("xmpp set presence", 4, server, server->connrec->show,
	    server->connrec->away_reason, server->connrec->priority);
	g_free_and_null(server->connrec->away_reason);
}
