gsearch_history_entry_save_history (GsearchHistoryEntry *entry)
{
	GVariant *history;
	GSList *items;
	gchar *key;
	GVariantBuilder item_builder;
	GVariantBuilder history_builder;
	GVariantIter *iter;
	GVariant     *item;
	GVariant     *history_list;
	GSList *list_iter;
	gchar *history_key;

	g_return_if_fail (GSEARCH_IS_HISTORY_ENTRY (entry));

	items = get_history_list (entry);
	key = get_history_key (entry);

	history = g_settings_get_value (entry->priv->settings,
				        "search-history");

	g_variant_builder_init (&item_builder, G_VARIANT_TYPE ("as"));
	for (list_iter = items; list_iter; list_iter = list_iter->next)
		g_variant_builder_add (&item_builder, "s", (gchar *) list_iter->data);

	g_variant_builder_init (&history_builder, G_VARIANT_TYPE ("a{sas}"));
	g_variant_builder_add (&history_builder, "{sas}", key, &item_builder);

	if (history) {
		g_variant_get (history, "a{sas}", &iter);
		while ((item = g_variant_iter_next_value (iter))) {
			g_variant_get (item, "{s@as}", &history_key, &history_list);
			if (g_strcmp0 (history_key, key) != 0)
				g_variant_builder_add (&history_builder, "{s@as}", history_key, history_list);
	 		g_free (history_key);
	 		g_variant_unref (history_list);
	 		g_variant_unref (item);
 		}
 		g_variant_iter_free (iter);
 		g_variant_unref (history);
 	}

	g_settings_set_value (entry->priv->settings,
			      "search-history",
			      g_variant_new ("a{sas}", &history_builder));

	g_slist_foreach (items, (GFunc) g_free, NULL);
	g_slist_free (items);
	g_free (key);
}
