soup_directory_input_stream_read (GInputStream  *input,
				  void          *buffer,
				  gsize          count,
				  GCancellable  *cancellable,
				  GError       **error)
{
	SoupDirectoryInputStream *stream = SOUP_DIRECTORY_INPUT_STREAM (input);
	gsize total, size;

	for (total = 0; total < count; total += size) {
		if (stream->buffer == NULL) {
			stream->buffer = soup_directory_input_stream_read_next_file (stream, cancellable, error);
			if (stream->buffer == NULL) {

				if (total)
					g_clear_error (error);
				return total;
			}
		}

		size = MIN (stream->buffer->length, count - total);
		memcpy ((char *)buffer + total, stream->buffer->data, size);
		if (size == stream->buffer->length) {
			soup_buffer_free (stream->buffer);
			stream->buffer = NULL;
		} else {
			SoupBuffer *sub = soup_buffer_new_subbuffer (stream->buffer,
								     size,
								     stream->buffer->length - size);
			soup_buffer_free (stream->buffer);
			stream->buffer = sub;
		}
	}

	return total;
}
