g_mime_stream_buffer_finalize (GObject *object)
{
	GMimeStreamBuffer *stream = (GMimeStreamBuffer *) object;

	if (stream->source)
		g_object_unref (stream->source);

	g_free (stream->buffer);

	G_OBJECT_CLASS (parent_class)->finalize (object);
}
