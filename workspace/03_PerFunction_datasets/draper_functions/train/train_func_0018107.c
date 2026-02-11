source_registry_object_path_table_remove (ESourceRegistry *registry,
                                          const gchar *object_path)
{
	GHashTable *object_path_table;
	gboolean removed;

	g_return_val_if_fail (object_path != NULL, FALSE);

	object_path_table = registry->priv->object_path_table;

	g_mutex_lock (&registry->priv->object_path_table_lock);

	removed = g_hash_table_remove (object_path_table, object_path);

	g_mutex_unlock (&registry->priv->object_path_table_lock);

	return removed;
}
