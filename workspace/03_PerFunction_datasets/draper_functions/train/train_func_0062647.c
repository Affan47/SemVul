mode_find_channel(IRC_CHANNEL_REC *channel)
{
	GSList *tmp;

	g_return_val_if_fail(channel != NULL, NULL);

	for (tmp = modes; tmp != NULL; tmp = tmp->next) {
		MODE_REC *rec = tmp->data;

		if (rec->channel == channel)
                        return rec;
	}

	return NULL;
}
