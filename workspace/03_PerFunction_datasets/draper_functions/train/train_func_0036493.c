outdata_type_metadata_collect (xmms_xform_t *xform)
{
	gint val;
	const char *mime;
	xmms_stream_type_t *type;

	type = xform->out_type;
	mime = xmms_stream_type_get_str (type, XMMS_STREAM_TYPE_MIMETYPE);
	if (strcmp (mime, "audio/pcm") != 0) {
		return;
	}

	val = xmms_stream_type_get_int (type, XMMS_STREAM_TYPE_FMT_FORMAT);
	if (val != -1) {
		const gchar *name = xmms_sample_name_get ((xmms_sample_format_t) val);
		xmms_xform_metadata_set_str (xform,
		                             XMMS_MEDIALIB_ENTRY_PROPERTY_SAMPLE_FMT,
		                             name);
	}

	val = xmms_stream_type_get_int (type, XMMS_STREAM_TYPE_FMT_SAMPLERATE);
	if (val != -1) {
		xmms_xform_metadata_set_int (xform,
		                             XMMS_MEDIALIB_ENTRY_PROPERTY_SAMPLERATE,
		                             val);
	}

	val = xmms_stream_type_get_int (type, XMMS_STREAM_TYPE_FMT_CHANNELS);
	if (val != -1) {
		xmms_xform_metadata_set_int (xform,
		                             XMMS_MEDIALIB_ENTRY_PROPERTY_CHANNELS,
		                             val);
	}
}
