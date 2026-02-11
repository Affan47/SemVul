xmmsc_playlist_rinsert (xmmsc_connection_t *c, const char *playlist, int pos, const char *url)
{
	xmmsc_result_t *res;
	char *enc_url;

	x_check_conn (c, NULL);
	x_api_error_if (!url, "with a NULL url", NULL);

	enc_url = xmmsc_medialib_encode_url (url);
	if (!enc_url)
		return NULL;

	res = xmmsc_playlist_rinsert_encoded (c, playlist, pos, enc_url);

	free (enc_url);

	return res;
}
