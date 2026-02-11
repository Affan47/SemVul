brasero_file_monitor_finalize (GObject *object)
{
	BraseroFileMonitorPrivate *priv;

	priv = BRASERO_FILE_MONITOR_PRIVATE (object);

	brasero_file_monitor_reset (BRASERO_FILE_MONITOR (object));

	if (priv->notify_id)
		g_source_remove (priv->notify_id);

	g_hash_table_destroy (priv->files);
	g_hash_table_destroy (priv->directories);

	G_OBJECT_CLASS (brasero_file_monitor_parent_class)->finalize (object);
}
