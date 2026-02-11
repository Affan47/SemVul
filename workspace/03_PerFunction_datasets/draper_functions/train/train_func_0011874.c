_g_uri_get_host (const char *uri)
{
	const char *idx;

	idx = strstr (uri, "://");
	if (idx == NULL)
		return g_strdup ("file://");

	idx = strstr (idx + 3, "/");
	if (idx == NULL) {
		char *scheme;

		scheme = _g_uri_get_scheme (uri);
		if (scheme == NULL)
			scheme = g_strdup ("file://");
		return scheme;
	}

	return g_strndup (uri, (idx - uri));
}
