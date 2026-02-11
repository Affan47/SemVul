soup_uri_new (const char *uri_string)
{
	SoupURI *uri;

	if (!uri_string)
		return g_slice_new0 (SoupURI);

	uri = soup_uri_new_with_base (NULL, uri_string);
	if (!uri)
		return NULL;
	if (!SOUP_URI_IS_VALID (uri)) {
		soup_uri_free (uri);
		return NULL;
	}

	return uri;
}
