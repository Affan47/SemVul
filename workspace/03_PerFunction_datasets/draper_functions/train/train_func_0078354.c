stream_seek (GMimeStream *stream, gint64 offset, GMimeSeekWhence whence)
{
	GMimeStreamBuffer *buffer = (GMimeStreamBuffer *) stream;
	gint64 real;

	if (buffer->source == NULL) {
		errno = EBADF;
		return -1;
	}

	switch (buffer->mode) {
	case GMIME_STREAM_BUFFER_BLOCK_WRITE:
		if (stream_flush (stream) != 0)
			return -1;

		if ((real = g_mime_stream_seek (buffer->source, offset, whence)) != -1) {
			stream->position = real;
			buffer->buflen = 0;
		}

		return real;
	case GMIME_STREAM_BUFFER_BLOCK_READ:
		return stream_seek_block_read (stream, offset, whence);
	case GMIME_STREAM_BUFFER_CACHE_READ:
		return stream_seek_cache_read (stream, offset, whence);
	default:

		errno = EINVAL;
		return -1;
	}
}
