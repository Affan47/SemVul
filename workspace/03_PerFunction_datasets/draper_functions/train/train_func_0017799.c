cmd_part (struct session *sess, char *tbuf, char *word[], char *word_eol[])
{
	char *chan = word[2];
	char *reason = word_eol[3];
	if (!*chan)
		chan = sess->channel;
	if ((*chan) && is_channel (sess->server, chan))
	{
		if (reason[0] == 0)
			reason = NULL;
		server_sendpart (sess->server, chan, reason);
		return TRUE;
	}
	return FALSE;
}
