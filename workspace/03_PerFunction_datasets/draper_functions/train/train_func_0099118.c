close_async_ready_get_info_cb (GOutputStream *stream,
			       GAsyncResult  *res,
			       AsyncData     *async)
{
	GError *error = NULL;

	gedit_debug (DEBUG_SAVER);


	if (g_cancellable_is_cancelled (async->cancellable))
	{
		async_data_free (async);
		return;
	}

	gedit_debug_message (DEBUG_SAVER, "Finished closing stream");

	if (!g_output_stream_close_finish (stream, res, &error))
	{
		gedit_debug_message (DEBUG_SAVER, "Closing stream error: %s", error->message);

		async_failed (async, error);
		return;
	}


	gedit_debug_message (DEBUG_SAVER, "Query info on file");
	g_file_query_info_async (async->saver->priv->location,
			         REMOTE_QUERY_ATTRIBUTES,
			         G_FILE_QUERY_INFO_NONE,
			         G_PRIORITY_HIGH,
			         async->cancellable,
			         (GAsyncReadyCallback) remote_get_info_cb,
			         async);
}
