source_webdav_update_properties_from_soup_uri (ESourceWebdav *webdav_extension)
{
	ESource *source;
	ESourceExtension *extension;
	SoupURI *soup_uri;
	const gchar *extension_name;


	g_mutex_lock (&webdav_extension->priv->property_lock);
	soup_uri = soup_uri_copy (webdav_extension->priv->soup_uri);
	g_mutex_unlock (&webdav_extension->priv->property_lock);

	extension = E_SOURCE_EXTENSION (webdav_extension);
	source = e_source_extension_ref_source (extension);

	g_object_set (
		extension,
		"resource-path", soup_uri->path,
		"resource-query", soup_uri->query,
		NULL);

	extension_name = E_SOURCE_EXTENSION_AUTHENTICATION;
	extension = e_source_get_extension (source, extension_name);

	g_object_set (
		extension,
		"host", soup_uri->host,
		"port", soup_uri->port,
		"user", soup_uri->user,
		NULL);

	extension_name = E_SOURCE_EXTENSION_SECURITY;
	extension = e_source_get_extension (source, extension_name);

	g_object_set (
		extension,
		"secure", (soup_uri->scheme == SOUP_URI_SCHEME_HTTPS),
		NULL);

	g_object_unref (source);

	soup_uri_free (soup_uri);
}
