ms_nick(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	const char *nick, *server;

	nick = parc > 1 ? parv[1] : "?";
	server = parc > 7 ? parv[7] : "?";

	sendto_wallops_flags(UMODE_WALLOP, &me,
			"Link %s cancelled, TS5 nickname %s on %s introduced (old server?)",
			client_p->name, nick, server);
	sendto_server(NULL, NULL, CAP_TS6, NOCAPS,
			":%s WALLOPS :Link %s cancelled, TS5 nickname %s on %s introduced (old server?)",
			me.id, client_p->name, nick, server);
	ilog(L_SERVER, "Link %s cancelled, TS5 nickname %s on %s introduced (old server?)",
			client_p->name, nick, server);

	exit_client(client_p, client_p, &me, "TS5 nickname introduced");

	return 0;
}
