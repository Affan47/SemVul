plugin_ui_disable_manager (EPluginUIHook *hook,
                           GtkUIManager *ui_manager,
                           const gchar *id,
                           gboolean remove)
{
	GHashTable *hash_table;
	GHashTable *ui_definitions;
	GList *keys;

	hash_table = hook->priv->registry;
	hash_table = g_hash_table_lookup (hash_table, ui_manager);

	if (hash_table == NULL)
		return;

	if (id != NULL)
		keys = g_list_prepend (NULL, (gpointer) id);
	else
		keys = g_hash_table_get_keys (hash_table);

	ui_definitions = hook->priv->ui_definitions;

	while (keys != NULL) {
		guint merge_id;
		gpointer data;

		id = keys->data;
		keys = g_list_delete_link (keys, keys);

		if (g_hash_table_lookup (ui_definitions, id) == NULL)
			continue;

		data = g_hash_table_lookup (hash_table, id);
		merge_id = GPOINTER_TO_UINT (data);


		if (merge_id > 0) {
			gtk_ui_manager_remove_ui (ui_manager, merge_id);
			gtk_ui_manager_ensure_update (ui_manager);
		}

		if (remove)
			g_hash_table_remove (hash_table, id);
		else
			g_hash_table_insert (hash_table, g_strdup (id), NULL);
	}
}
