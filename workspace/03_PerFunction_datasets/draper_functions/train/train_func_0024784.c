nicklist_find_multiple(CHANNEL_REC *channel, const char *mask)
{
	GSList *nicks, *tmp, *next;

	g_return_val_if_fail(IS_CHANNEL(channel), NULL);
	g_return_val_if_fail(mask != NULL, NULL);

	nicks = nicklist_getnicks(channel);
	for (tmp = nicks; tmp != NULL; tmp = next) {
		NICK_REC *nick = tmp->data;

		next = tmp->next;
		if (!mask_match_address(channel->server, mask,
					nick->nick, nick->host))
                        nicks = g_slist_remove(nicks, tmp->data);
	}

	return nicks;
}
