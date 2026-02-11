print_nick_change(SERVER_REC *server, const char *newnick,
			      const char *oldnick, const char *address,
			      int ownnick)
{
	GSList *tmp, *windows;
	int msgprint;

	msgprint = FALSE;


	windows = NULL;
	for (tmp = server->channels; tmp != NULL; tmp = tmp->next) {
		CHANNEL_REC *channel = tmp->data;
		WINDOW_REC *window =
			window_item_window((WI_ITEM_REC *) channel);

		if (nicklist_find(channel, newnick) == NULL ||
		    g_slist_find(windows, window) != NULL)
			continue;

		windows = g_slist_append(windows, window);
		print_nick_change_channel(server, channel->visible_name,
					  newnick, oldnick, address, ownnick);
		msgprint = TRUE;
	}

	g_slist_free(windows);

	if (!msgprint && ownnick) {
		printformat(server, NULL, MSGLEVEL_NICKS,
			    TXT_YOUR_NICK_CHANGED, oldnick, newnick, "",
			    address);
	}
}
