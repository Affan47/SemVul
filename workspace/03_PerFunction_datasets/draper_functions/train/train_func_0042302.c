irc_channel_find_server(SERVER_REC *server,
					    const char *channel)
{
	GSList *tmp;

	for (tmp = server->channels; tmp != NULL; tmp = tmp->next) {
		CHANNEL_REC *rec = tmp->data;

		if (rec->chat_type != server->chat_type)
                        continue;


		if (IRC_SERVER(server)->nick_comp_func(channel, rec->name) == 0)
			return rec;

		if (IRC_SERVER(server)->nick_comp_func(channel, rec->visible_name) == 0)
			return rec;
	}

	return NULL;
}
