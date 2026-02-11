gconf_cleaner_pairs_free(GSList *list)
{
	GSList *l;

	g_return_if_fail (list != NULL);

	for (l = list; l != NULL; l = g_slist_next(l)) {
		g_free(l->data);
		l = g_slist_next(l);
		gconf_value_free(l->data);
	}
	g_slist_free(list);
}
