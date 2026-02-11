WriteZStream (ZStream *stream, guchar *buffer, gint length)
{
	gint n;
	gint status;
	z_stream *zs;

	if (stream == NULL || buffer == NULL || length < 0)
		return ARGUMENT_ERROR;

	if (stream->eof)
		return IO_ERROR;

	zs = stream->stream;
	zs->next_in = buffer;
	zs->avail_in = length;
	while (zs->avail_in > 0) {
		if (zs->avail_out == 0) {
			zs->next_out = stream->buffer;
			zs->avail_out = BUFFER_SIZE;
		}
		status = deflate (stream->stream, Z_NO_FLUSH);
		if (status != Z_OK && status != Z_STREAM_END)
			return status;

		if (zs->avail_out == 0) {
			n = write_to_managed (stream);
			if (n < 0)
				return n;
		}
	}
	return length;
}
