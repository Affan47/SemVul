mime_filter_gzip_finalize (GObject *object)
{
	CamelMimeFilterGZipPrivate *priv;

	priv = CAMEL_MIME_FILTER_GZIP_GET_PRIVATE (object);

	if (priv->mode == CAMEL_MIME_FILTER_GZIP_MODE_ZIP)
		deflateEnd (priv->stream);
	else
		inflateEnd (priv->stream);

	g_free (priv->stream);


	G_OBJECT_CLASS (camel_mime_filter_gzip_parent_class)->finalize (object);
}
