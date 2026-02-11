build_id_list (const gchar * const *seq)
{
	GSList *list;
	const gchar *eol;
	gint i;

	list = NULL;
	for (i = 0; seq[i]; i++) {
		ECalComponentId *id;
		id = g_new (ECalComponentId, 1);


		eol = strchr (seq[i], '\n');
		if (eol) {
			id->uid = g_strndup (seq[i], eol - seq[i]);
			id->rid = g_strdup (eol + 1);
		} else {
			id->uid = g_strdup (seq[i]);
			id->rid = NULL;
		}

		list = g_slist_prepend (list, id);
	}

	return g_slist_reverse (list);
}
