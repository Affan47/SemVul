camel_cipher_canonical_to_stream (CamelMimePart *part,
                                  guint32 flags,
                                  CamelStream *ostream,
                                  GCancellable *cancellable,
                                  GError **error)
{
	CamelStream *filter;
	CamelMimeFilter *canon;
	gint res = -1;

	g_return_val_if_fail (CAMEL_IS_MIME_PART (part), -1);
	g_return_val_if_fail (CAMEL_IS_STREAM (ostream), -1);

	if (flags & (CAMEL_MIME_FILTER_CANON_FROM | CAMEL_MIME_FILTER_CANON_STRIP))
		cc_prepare_sign (part);

	filter = camel_stream_filter_new (ostream);
	canon = camel_mime_filter_canon_new (flags);
	camel_stream_filter_add (CAMEL_STREAM_FILTER (filter), canon);
	g_object_unref (canon);

	if (camel_data_wrapper_write_to_stream_sync (
		CAMEL_DATA_WRAPPER (part), filter, cancellable, error) != -1
	    && camel_stream_flush (filter, cancellable, error) != -1)
		res = 0;

	g_object_unref (filter);


	if (G_IS_SEEKABLE (ostream))
		g_seekable_seek (
			G_SEEKABLE (ostream), 0,
			G_SEEK_SET, NULL, NULL);

	return res;
}
