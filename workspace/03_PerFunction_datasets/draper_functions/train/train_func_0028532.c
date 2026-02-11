cmd_quit (struct session *sess, char *tbuf, char *word[], char *word_eol[])
{
	if (*word_eol[2])
		sess->quitreason = word_eol[2];
	sess->server->disconnect (sess, TRUE, -1);
	sess->quitreason = NULL;
	return 2;
}
