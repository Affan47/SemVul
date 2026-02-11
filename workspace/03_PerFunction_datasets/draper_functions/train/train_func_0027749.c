write_file__stream_write_ready_cb (GObject      *source_object,
				   GAsyncResult *result,
				   gpointer      user_data)
{
	GOutputStream *stream = (GOutputStream *) source_object;
	WriteData     *write_data = user_data;
	GError        *error = NULL;
	gssize         count;

	count = g_output_stream_write_finish (stream, result, &error);
	write_data->written += count;

	if ((count == 0) || (write_data->written == write_data->count)) {
		g_output_stream_flush_async (stream,
					     write_data->io_priority,
					     write_data->cancellable,
					     write_file__stream_flush_cb,
					     user_data);
		return;
	}

	g_output_stream_write_async (stream,
				     write_data->buffer + write_data->written,
				     write_data->count - write_data->written,
				     write_data->io_priority,
				     write_data->cancellable,
				     write_file__stream_write_ready_cb,
				     write_data);
}
