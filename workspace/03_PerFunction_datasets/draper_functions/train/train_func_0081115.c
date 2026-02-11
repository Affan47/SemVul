optlist_find(GSList *optlist, const char *option)
{
	while (optlist != NULL) {
		char *name = optlist->data;
		if (iscmdtype(*name)) name++;

		if (g_strcasecmp(name, option) == 0)
			return optlist;

		optlist = optlist->next;
	}

	return NULL;
}
