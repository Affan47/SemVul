stream_filter_close (CamelStream *stream,
                     GCancellable *cancellable,
                     GError **error)
{
	CamelStreamFilterPrivate *priv;

	priv = CAMEL_STREAM_FILTER_GET_PRIVATE (stream);


	if (!priv->last_was_read)
		stream_filter_flush (stream, cancellable, NULL);

	return camel_stream_close (priv->source, cancellable, error);
}
