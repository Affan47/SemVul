irc_nicklist_insert(IRC_CHANNEL_REC *channel, const char *nick,
			      int op, int halfop, int voice, int send_massjoin)
{
	NICK_REC *rec;

	g_return_val_if_fail(IS_IRC_CHANNEL(channel), NULL);
	g_return_val_if_fail(nick != NULL, NULL);

	rec = g_new0(NICK_REC, 1);
	rec->nick = g_strdup(nick);

	if (op) rec->op = TRUE;
	if (halfop) rec->halfop = TRUE;
	if (voice) rec->voice = TRUE;
	rec->send_massjoin = send_massjoin;

	nicklist_insert(CHANNEL(channel), rec);
	return rec;
}
