reload_if_needed (GtkSourceStyleSchemeManager *mgr)
{
	GSList *ids = NULL;
	GSList *files;
	GSList *l;
	GHashTable *schemes_hash;

	if (!mgr->priv->need_reload)
		return;

	schemes_hash = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_object_unref);

	files = _gtk_source_view_get_file_list ((gchar **)gtk_source_style_scheme_manager_get_search_path (mgr),
						SCHEME_FILE_SUFFIX,
						FALSE);

	for (l = files; l != NULL; l = l->next)
	{
		GtkSourceStyleScheme *scheme;
		gchar *filename;

		filename = l->data;

		scheme = _gtk_source_style_scheme_new_from_file (filename);

		if (scheme != NULL)
		{
			const gchar *id = gtk_source_style_scheme_get_id (scheme);
			GtkSourceStyleScheme *old;

			old = g_hash_table_lookup (schemes_hash, id);

			if (old != NULL)
				ids = ids_list_remove (ids, id, TRUE);

			ids = g_slist_prepend (ids, g_strdup (id));
			g_hash_table_insert (schemes_hash, g_strdup (id), scheme);
		}
	}

	ids = check_parents (ids, schemes_hash);

	g_slist_foreach (files, (GFunc) g_free, NULL);
	g_slist_free (files);

	free_schemes (mgr);

	mgr->priv->need_reload = FALSE;
	mgr->priv->schemes_hash = schemes_hash;

	mgr->priv->ids = slist_to_strv (ids);
	g_slist_free (ids);

}
