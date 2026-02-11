account_move(guint32 key1, guint32 key2)
{
GList *list;

	list = g_list_first(GLOBALS->ope_list);
	while (list != NULL)
	{
	Transaction *entry = list->data;
		if(entry->kacc == key1)
			entry->kacc = key2;
		if(entry->kxferacc == key1)
			entry->kxferacc = key2;
		list = g_list_next(list);
	}

	list = g_list_first(GLOBALS->arc_list);
	while (list != NULL)
	{
	Archive *entry = list->data;
		if(entry->kacc == key1)
			entry->kacc = key2;
		if(entry->kxferacc == key1)
			entry->kxferacc = key2;
		list = g_list_next(list);
	}
}
