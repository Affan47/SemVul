write_file_chunk (AsyncData *async)
{
	GeditDocumentLoader *loader;
	gssize bytes_written;
	GError *error = NULL;

	loader = async->loader;


	bytes_written = g_output_stream_write (G_OUTPUT_STREAM (loader->priv->output),
					       loader->priv->buffer,
					       async->read,
					       async->cancellable,
					       &error);

	gedit_debug_message (DEBUG_LOADER, "Written: %" G_GSSIZE_FORMAT, bytes_written);
	if (bytes_written == -1)
	{
		gedit_debug_message (DEBUG_LOADER, "Write error: %s", error->message);
		async_failed (async, error);
		return;
	}


	gedit_document_loader_loading (loader,
				       FALSE,
				       NULL);

	read_file_chunk (async);
}
