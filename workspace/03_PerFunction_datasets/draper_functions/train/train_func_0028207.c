add_monitor_for_directory (GthFileSourceVfs *file_source_vfs,
			   GFile            *file)
{
	GFile *parent;

	parent = g_object_ref (file);
	while (parent != NULL) {
		GFile *tmp;

		if (g_hash_table_lookup (file_source_vfs->priv->monitors, parent) == NULL) {
			GFileMonitor *monitor;

			monitor = g_file_monitor_directory (parent, 0, NULL, NULL);
			if (monitor != NULL) {
				g_hash_table_insert (file_source_vfs->priv->monitors, g_object_ref (parent), monitor);
				g_signal_connect (monitor, "changed", G_CALLBACK (monitor_changed_cb), file_source_vfs);
			}
		}

		tmp = g_file_get_parent (parent);
		g_object_unref (parent);
		parent = tmp;
	}
}
