mime_filter_charset_finalize (GObject *object)
{
	CamelMimeFilterCharsetPrivate *priv;

	priv = CAMEL_MIME_FILTER_CHARSET_GET_PRIVATE (object);

	g_free (priv->from);
	g_free (priv->to);

	if (priv->ic != (iconv_t) -1) {
		camel_iconv_close (priv->ic);
		priv->ic = (iconv_t) -1;
	}


	G_OBJECT_CLASS (camel_mime_filter_charset_parent_class)->finalize (object);
}
