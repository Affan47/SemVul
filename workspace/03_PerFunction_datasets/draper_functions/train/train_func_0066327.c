soup_converter_wrapper_convert (GConverter *converter,
				const void *inbuf,
				gsize       inbuf_size,
				void       *outbuf,
				gsize       outbuf_size,
				GConverterFlags flags,
				gsize      *bytes_read,
				gsize      *bytes_written,
				GError    **error)
{
	SoupConverterWrapperPrivate *priv = SOUP_CONVERTER_WRAPPER (converter)->priv;

	if (priv->base_converter) {
		return soup_converter_wrapper_real_convert (converter,
							    inbuf, inbuf_size,
							    outbuf, outbuf_size,
							    flags, bytes_read,
							    bytes_written, error);
	} else {
		return soup_converter_wrapper_fallback_convert (converter,
								inbuf, inbuf_size,
								outbuf, outbuf_size,
								flags, bytes_read,
								bytes_written, error);
	}
}
