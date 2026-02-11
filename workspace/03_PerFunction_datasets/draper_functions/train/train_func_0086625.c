load_file__file_read_cb (GObject      *source_object,
			 GAsyncResult *result,
			 gpointer      user_data)
{
	LoadData *load_data = user_data;
	GError   *error = NULL;

	load_data->stream = (GInputStream *) g_file_read_finish (G_FILE (source_object), result, &error);
	if (load_data->stream == NULL) {
		load_data->callback (&load_data->buffer, -1, error, load_data->user_data);
		load_data_free (load_data);
		return;
	}

	load_data->count = 0;
	g_input_stream_read_async (load_data->stream,
				   load_data->tmp_buffer,
				   BUFFER_SIZE,
				   load_data->io_priority,
				   load_data->cancellable,
				   load_file__stream_read_cb,
				   load_data);
}
