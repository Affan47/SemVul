g3d_stream_buffer_read(gpointer ptr, gsize size, gpointer data)
{
	G3DStreamBuffer *sbuf = (G3DStreamBuffer *)data;
	guint8 *outbufp = (guint8 *)ptr;
	gsize max_size;

	max_size = MIN(sbuf->size - sbuf->offset, size);
	memcpy(outbufp, sbuf->buffer + sbuf->offset, max_size);
	sbuf->offset += max_size;

	return max_size;
}
