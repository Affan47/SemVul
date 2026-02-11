xmms_medialib_client_set_property_string (xmms_medialib_t *medialib,
                                          gint32 entry, const gchar *source,
                                          const gchar *key, const gchar *value,
                                          xmms_error_t *error)
{
	guint32 sourceid;
	xmms_medialib_session_t *session;

	if (g_ascii_strcasecmp (source, "server") == 0) {
		xmms_error_set (error, XMMS_ERROR_GENERIC,
		                "Can't write to source server!");
		return;
	}

	session = xmms_medialib_begin_write ();
	sourceid = xmms_medialib_source_to_id (session, source);

	xmms_medialib_entry_property_set_str_source (session, entry, key, value,
	                                             sourceid);
	xmms_medialib_end (session);

	xmms_medialib_entry_send_update (entry);
}
