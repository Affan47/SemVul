ensure_languages (GtkSourceLanguageManager *lm)
{
	GSList *filenames, *l;
	GPtrArray *ids_array = NULL;

	if (lm->priv->language_ids != NULL)
		return;

	lm->priv->language_ids = g_hash_table_new_full (g_str_hash, g_str_equal,
							g_free, g_object_unref);

	filenames = _gtk_source_view_get_file_list ((gchar **)gtk_source_language_manager_get_search_path (lm),
						    LANG_FILE_SUFFIX,
						    TRUE);

	for (l = filenames; l != NULL; l = l->next)
	{
		GtkSourceLanguage *lang;
		gchar *filename;

		filename = l->data;

		lang = _gtk_source_language_new_from_file (filename, lm);

		if (lang == NULL)
		{
			g_warning ("Error reading language specification file '%s'", filename);
			continue;
		}

		if (g_hash_table_lookup (lm->priv->language_ids, lang->priv->id) == NULL)
		{
			g_hash_table_insert (lm->priv->language_ids,
					     g_strdup (lang->priv->id),
					     lang);

			if (ids_array == NULL)
				ids_array = g_ptr_array_new ();

			g_ptr_array_add (ids_array, g_strdup (lang->priv->id));
		}
		else
		{
			g_object_unref (lang);
		}
	}

	if (ids_array != NULL)
	{


		g_ptr_array_sort_with_data (ids_array,
		                            (GCompareDataFunc)language_compare,
		                            lm->priv->language_ids);


		g_ptr_array_add (ids_array, NULL);

		lm->priv->ids = (gchar **)g_ptr_array_free (ids_array, FALSE);
	}

	g_slist_free_full (filenames, g_free);
}
