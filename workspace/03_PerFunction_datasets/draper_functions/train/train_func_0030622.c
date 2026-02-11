add_source (ECollectionBackend *collection,
            OwnCloudSourceFoundCb found_cb,
            gpointer user_data,
            OwnCloudSourceType source_type,
            SoupURI *base_uri,
            const gchar *href,
            const gchar *display_name,
            const gchar *color)
{
	SoupURI *uri = NULL;

	if (!href || !display_name)
		return;

	if (!strstr (href, "://")) {
		soup_uri_set_path (base_uri, href);
	} else {
		uri = soup_uri_new (href);
	}

	found_cb (
		collection,
		source_type,
		uri ? uri : base_uri,
		display_name,
		color,
		user_data);

	if (uri)
		soup_uri_free (uri);
}
