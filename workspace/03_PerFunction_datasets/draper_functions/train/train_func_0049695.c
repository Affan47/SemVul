is_stored_on_server (ECalBackendCalDAV *cbdav,
                     const gchar *uri)
{
	SoupURI *my_uri, *test_uri;
	gboolean res;

	g_return_val_if_fail (E_IS_CAL_BACKEND_CALDAV (cbdav), FALSE);
	g_return_val_if_fail (cbdav->priv->uri != NULL, FALSE);
	g_return_val_if_fail (uri != NULL, FALSE);

	my_uri = soup_uri_new (cbdav->priv->uri);
	g_return_val_if_fail (my_uri != NULL, FALSE);

	test_uri = soup_uri_new (uri);
	if (!test_uri) {
		soup_uri_free (my_uri);
		return FALSE;
	}

	res = my_uri->host && test_uri->host && g_ascii_strcasecmp (my_uri->host, test_uri->host) == 0;

	soup_uri_free (my_uri);
	soup_uri_free (test_uri);

	return res;
}
