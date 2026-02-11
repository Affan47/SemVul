playlist_exists (cli_infos_t *infos, const gchar *playlist)
{
	gboolean retval = FALSE;
	xmmsc_result_t *res;
	xmmsv_t *val;

	res = xmmsc_coll_get (infos->sync, playlist, XMMS_COLLECTION_NS_PLAYLISTS);
	xmmsc_result_wait (res);

	val = xmmsc_result_get_value (res);

	if (!xmmsv_is_error (val)) {
		retval = TRUE;
	}

	xmmsc_result_unref (res);

	return retval;
}
