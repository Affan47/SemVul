xmms_playlist_client_add_url (xmms_playlist_t *playlist, const gchar *plname,
                              const gchar *nurl, xmms_error_t *err)
{
	xmms_medialib_entry_t entry = 0;
	xmms_medialib_session_t *session = xmms_medialib_begin_write ();

	entry = xmms_medialib_entry_new_encoded (session, nurl, err);
	xmms_medialib_end (session);

	if (entry) {
		xmms_playlist_add_entry (playlist, plname, entry, err);
	}

}
