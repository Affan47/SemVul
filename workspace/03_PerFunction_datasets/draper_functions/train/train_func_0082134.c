xmms_id3v1_parse (xmms_xform_t *xform, guchar *buf)
{
	xmms_config_property_t *config;
	id3v1tag_t *tag = (id3v1tag_t *) buf;
	const char *encoding;
	const gchar *metakey;

	if (strncmp (tag->tag, "TAG", 3) != 0) {
		return FALSE;
	}

	XMMS_DBG ("Found ID3v1 TAG!");

	config = xmms_xform_config_lookup (xform, "id3v1_encoding");
	g_return_val_if_fail (config, FALSE);
	encoding = xmms_config_property_get_string (config);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_ARTIST;
	xmms_id3v1_set (xform, metakey, tag->artist,
	                sizeof (tag->artist), encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_ALBUM;
	xmms_id3v1_set (xform, metakey, tag->album,
	                sizeof (tag->album), encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_TITLE;
	xmms_id3v1_set (xform, metakey, tag->title,
	                sizeof (tag->title), encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_YEAR;
	xmms_id3v1_set (xform, metakey, tag->year,
	                sizeof (tag->year), encoding);

	metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_GENRE;
	if (!xmms_xform_metadata_has_val (xform, metakey)) {
		if (tag->genre >= G_N_ELEMENTS (id3_genres)) {
			metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_GENRE;
			xmms_xform_metadata_set_str (xform, metakey, "Unknown");
		} else {
			metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_GENRE;
			xmms_xform_metadata_set_str (xform, metakey,
			                             id3_genres[tag->genre]);
		}
	}

	if (tag->u.v1_1.__zero == 0 && tag->u.v1_1.track_number > 0) {

		xmms_id3v1_set (xform, XMMS_MEDIALIB_ENTRY_PROPERTY_COMMENT,
		                tag->u.v1_1.comment, sizeof (tag->u.v1_1.comment),
		                encoding);

		metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_TRACKNR;
		if (!xmms_xform_metadata_has_val (xform, metakey)) {
			metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_TRACKNR;
			xmms_xform_metadata_set_int (xform, metakey,
			                             tag->u.v1_1.track_number);
		}
	} else {
		metakey = XMMS_MEDIALIB_ENTRY_PROPERTY_COMMENT;
		xmms_id3v1_set (xform, metakey, tag->u.v1_0.comment,
		                sizeof (tag->u.v1_0.comment), encoding);
	}

	return TRUE;
}
