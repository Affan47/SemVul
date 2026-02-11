write_metadata_ready_cb (GObject      *source_object,
		 	 GAsyncResult *result,
		 	 gpointer      user_data)
{
	GthTagTask *self = user_data;
	GthMonitor *monitor;
	GList      *scan;
	GError     *error = NULL;

	if (! _g_write_metadata_finish (result, &error)) {
		gth_task_completed (GTH_TASK (self), error);
		return;
	}

	monitor = gth_main_get_default_monitor ();
	for (scan = self->priv->file_data_list; scan; scan = scan->next) {
		GthFileData *file_data = scan->data;
		GFile       *parent;
		GList       *files;

		parent = g_file_get_parent (file_data->file);
		files = g_list_prepend (NULL, g_object_ref (file_data->file));
		gth_monitor_folder_changed (monitor, parent, files, GTH_MONITOR_EVENT_CHANGED);
		gth_monitor_metadata_changed (monitor, file_data);

		_g_object_list_unref (files);
		g_object_unref (parent);
	}

	gth_task_completed (GTH_TASK (self), NULL);
}
