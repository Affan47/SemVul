cmd_wallchan (struct session *sess, char *tbuf, char *word[],
				  char *word_eol[])
{
	GSList *list;

	if (*word_eol[2])
	{
		list = sess_list;
		while (list)
		{
			sess = list->data;
			if (sess->type == SESS_CHANNEL)
			{
				message_tags_data no_tags = MESSAGE_TAGS_DATA_INIT;

				inbound_chanmsg (sess->server, NULL, sess->channel,
									  sess->server->nick, word_eol[2], TRUE, FALSE,
									  &no_tags);
				sess->server->p_message (sess->server, sess->channel, word_eol[2]);
			}
			list = list->next;
		}
		return TRUE;
	}
	return FALSE;
}
