load_local_archive_list_ready_cb (GObject      *source_object,
				  GAsyncResult *result,
				  gpointer      user_data)
{
	XferData *xfer_data = user_data;
	GError   *error = NULL;

	if (! fr_command_handle_process_error (FR_COMMAND (xfer_data->archive), result, &error))

		return;

	_fr_command_load_complete (xfer_data, error);

	_g_error_free (error);
}
