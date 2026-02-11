soup_converter_wrapper_set_property (GObject      *object,
				     guint         prop_id,
				     const GValue *value,
				     GParamSpec   *pspec)
{
	SoupConverterWrapperPrivate *priv = SOUP_CONVERTER_WRAPPER (object)->priv;

	switch (prop_id) {
	case PROP_BASE_CONVERTER:
		priv->base_converter = g_value_dup_object (value);
		if (G_IS_ZLIB_DECOMPRESSOR (priv->base_converter)) {
			GZlibCompressorFormat format;

			g_object_get (G_OBJECT (priv->base_converter),
				      "format", &format,
				      NULL);
			if (format == G_ZLIB_COMPRESSOR_FORMAT_ZLIB)
				priv->try_deflate_fallback = TRUE;
		}
		break;

	case PROP_MESSAGE:
		priv->msg = g_value_dup_object (value);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
