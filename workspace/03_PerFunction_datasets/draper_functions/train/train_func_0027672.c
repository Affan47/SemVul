enumerate_children_cb (GObject *source,
		       GAsyncResult *res,
		       gpointer user_data)
{
	GFileEnumerator *enumerator;
	NautilusTrashMonitor *trash_monitor = user_data;

	enumerator = g_file_enumerate_children_finish (G_FILE (source), res, NULL);
	if (!enumerator) {
		update_empty_info (trash_monitor, TRUE);
		g_object_unref (trash_monitor);
		return;
	}

	g_file_enumerator_next_files_async (enumerator, 1,
					    G_PRIORITY_DEFAULT, NULL,
					    enumerate_next_files_cb, trash_monitor);
	g_object_unref (enumerator);
}
