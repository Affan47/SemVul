get_nick_flags(SERVER_REC *server)
{
	IRC_SERVER_REC *irc_server = (IRC_SERVER_REC *) server;
	const char *prefix =
		g_hash_table_lookup(irc_server->isupport, "PREFIX");

	prefix = prefix == NULL ? NULL : strchr(prefix, ')');
	return prefix == NULL ? "" : prefix+1;
}
