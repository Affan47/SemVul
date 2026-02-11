finish_rename (NautilusFile *file, gboolean stop_timer, GError *error)
{
	NautilusRenameData *data;

	data = g_object_get_data (G_OBJECT (file), NEW_NAME_TAG);
	if (data == NULL) {
		return;
	}


	nautilus_file_cancel (file, rename_callback, NULL);
	if (stop_timer) {
		eel_timed_wait_stop (cancel_rename_callback, file);
	}

	if (data->callback != NULL) {
		data->callback (file, NULL, error, data->callback_data);
	}


	g_object_set_data (G_OBJECT (file), NEW_NAME_TAG, NULL);
}
