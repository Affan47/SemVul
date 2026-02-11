xmms_id3v1_parse (xmms_xform_t *xform, guchar *buf)
{
	xmms_config_property_t *config;
	const char *encoding;
	const gchar *metakey;
	xmmsv_t *bb;
	unsigned char data[32];

	bb = xmmsv_bitbuffer_new_ro (buf, 128);

	xmmsv_bitbuffer_get_data (bb, data, 3);

	if (memcmp (data, "TAG", 3) != 0) {
		xmmsv_unref (bb);
		return FALSE;
	}

	XMMS_DBG ("Found ID3v1 TAG!");

	config = xmms_xform_config_lookup (xform, "id3v1_encoding");
	g_return_val_if_fail (config, FALSE);
	encoding = xmms_config_property_get_string (config);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_TITLE;
	xmmsv_bitbuffer_get_data (bb, data, 30);
	xmms_id3v1_set (xform, metakey, data, 30, encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_ARTIST;
	xmmsv_bitbuffer_get_data (bb, data, 30);
	xmms_id3v1_set (xform, metakey, data, 30, encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_ALBUM;
	xmmsv_bitbuffer_get_data (bb, data, 30);
	xmms_id3v1_set (xform, metakey, data, 30, encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_YEAR;
	xmmsv_bitbuffer_get_data (bb, data, 4);
	xmms_id3v1_set (xform, metakey, data, 4, encoding);

	xmmsv_bitbuffer_get_data (bb, data, 30);


	if (data[28] == '\0' && data[29]) {
		metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_COMMENT;
		xmms_id3v1_set (xform, metakey, data, 28, encoding);
		metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_TRACKNR;
		if (!xmms_xform_metadata_has_val (xform, metakey)) {
			xmms_xform_metadata_set_int (xform, metakey, data[29]);
		}
	} else {
		metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_COMMENT;
		xmms_id3v1_set (xform, metakey, data, 30, encoding);
	}


	xmmsv_bitbuffer_get_data (bb, data, 1);
	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_GENRE;
	if (data[0] >= G_N_ELEMENTS (id3_genres)) {
		xmms_xform_metadata_set_str (xform, metakey, "Unknown");
	} else {
		xmms_xform_metadata_set_str (xform, metakey, id3_genres[data[0]]);
	}


	xmmsv_unref (bb);
	return TRUE;
}
