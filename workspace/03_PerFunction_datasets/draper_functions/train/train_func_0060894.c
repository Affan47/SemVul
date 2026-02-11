g_mime_filter_gzip_finalize (GObject *object)
{
	GMimeFilterGZip *gzip = (GMimeFilterGZip *) object;
	struct _GMimeFilterGZipPrivate *priv = gzip->priv;

	if (gzip->mode == GMIME_FILTER_GZIP_MODE_ZIP)
		deflateEnd (priv->stream);
	else
		inflateEnd (priv->stream);

	g_free (priv->stream);
	g_free (priv);

	G_OBJECT_CLASS (parent_class)->finalize (object);
}
