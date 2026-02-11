banlist_find(GSList *list, const char *ban)
{
	GSList *tmp;

	g_return_val_if_fail(ban != NULL, NULL);

	for (tmp = list; tmp != NULL; tmp = tmp->next) {
		BAN_REC *rec = tmp->data;

		if (g_strcasecmp(rec->ban, ban) == 0)
			return rec;
	}

	return NULL;
}
