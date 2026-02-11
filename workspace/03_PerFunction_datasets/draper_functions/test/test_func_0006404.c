writeback_file_finished  (GObject      *source_object,
                          GAsyncResult *res,
                          gpointer      user_data)
{
	WritebackFileData *data = user_data;
	GError *error = NULL;

	g_dbus_connection_call_finish (G_DBUS_CONNECTION (source_object),
	                               res, &error);

	if (error && error->code == G_DBUS_ERROR_NO_REPLY && data->retries < 5) {


		g_debug ("Retrying write-back after unmount (timeout in 5 seconds)");
		tracker_miner_fs_writeback_notify (data->fs, data->file, NULL);

		data->retry_timeout = g_timeout_add_seconds (5, retry_idle, data);
		data->retries++;

	} else {
		tracker_miner_fs_writeback_notify (data->fs, data->file, error);
		writeback_file_data_free (data);
	}
}
