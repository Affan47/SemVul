nemo_file_cancel_call_when_ready (NemoFile *file,
				      NemoFileCallback callback,
				      gpointer callback_data)
{
	g_return_if_fail (callback != NULL);

	if (file == NULL) {
		return;
	}

	g_return_if_fail (NEMO_IS_FILE (file));

	NEMO_FILE_CLASS (G_OBJECT_GET_CLASS (file))->cancel_call_when_ready
		(file, callback, callback_data);
}
