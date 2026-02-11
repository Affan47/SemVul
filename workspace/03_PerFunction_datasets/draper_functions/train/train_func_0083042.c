enumerate_next_files_cb (GObject *source,
			 GAsyncResult *res,
			 gpointer user_data)
{
	NautilusTrashMonitor *trash_monitor = user_data;
	GList *infos;

	infos = g_file_enumerator_next_files_finish (G_FILE_ENUMERATOR (source), res, NULL);
	if (!infos) {
		update_empty_info (trash_monitor, TRUE);
	} else {
		update_empty_info (trash_monitor, FALSE);
		g_list_free_full (infos, g_object_unref);
	}

	g_object_unref (trash_monitor);
}
