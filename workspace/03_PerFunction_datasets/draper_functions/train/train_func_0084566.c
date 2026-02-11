plugin_ui_enable_hook (EPluginUIHook *hook)
{
	GHashTable *hash_table;
	GHashTableIter iter;
	gpointer key;


	hash_table = hook->priv->registry;
	g_hash_table_iter_init (&iter, hash_table);

	while (g_hash_table_iter_next (&iter, &key, NULL)) {
		GtkUIManager *ui_manager = key;
		plugin_ui_enable_manager (hook, ui_manager, NULL);
	}
}
