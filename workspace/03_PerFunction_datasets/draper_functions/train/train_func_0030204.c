xmms_magic_plugin_init (xmms_xform_t *xform)
{
	xmms_magic_checker_t c;
	gchar *res;
	const gchar *url;
	xmms_config_property_t *cv;

	c.xform = xform;
	c.read = c.offset = 0;
	c.alloc = 128;
	c.buf = g_malloc (c.alloc);

	cv = xmms_xform_config_lookup (xform, "dumpcount");
	c.dumpcount = xmms_config_property_get_int (cv);

	url = xmms_xform_indata_find_str (xform, XMMS_STREAM_TYPE_URL);

	res = xmms_magic_match (&c, url);
	if (res) {
		xmms_xform_metadata_set_str (xform, XMMS_MEDIALIB_ENTRY_PROPERTY_MIME, res);
		xmms_xform_outdata_type_add (xform,
		                             XMMS_STREAM_TYPE_MIMETYPE,
		                             res,
		                             XMMS_STREAM_TYPE_END);
	}

	g_free (c.buf);

	return !!res;
}
