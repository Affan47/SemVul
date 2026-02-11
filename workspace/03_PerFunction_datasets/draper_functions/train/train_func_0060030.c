same_source_name_exists (ESourceSelector *selector,
                         const gchar *display_name)
{
	GHashTable *source_index;
	GHashTableIter iter;
	gpointer key;

	source_index = selector->priv->source_index;
	g_hash_table_iter_init (&iter, source_index);

	while (g_hash_table_iter_next (&iter, &key, NULL)) {
		ESource *source = E_SOURCE (key);
		const gchar *source_name;

		source_name = e_source_get_display_name (source);
		if (g_strcmp0 (display_name, source_name) == 0)
			return TRUE;
	}

	return FALSE;
}
