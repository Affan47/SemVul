get_proxy_uri_sync (SoupProxyURIResolver  *resolver,
		    SoupURI		  *uri,
		    GCancellable	  *cancellable,
		    SoupURI		 **proxy_uri)
{
	SoupProxyResolverDefaultPrivate *priv = SOUP_PROXY_RESOLVER_DEFAULT_GET_PRIVATE (resolver);
	GError *error = NULL;
	char** proxy_uris = NULL;
	char *uri_string;
	guint status = SOUP_STATUS_OK;

	uri_string = soup_uri_to_string (uri, FALSE);

	proxy_uris = g_proxy_resolver_lookup (priv->gproxy_resolver,
					      uri_string,
					      cancellable,
					      &error);

	g_free (uri_string);

	if (error || proxy_uris == NULL || proxy_uris[0] == NULL) {
		status = SOUP_STATUS_CANT_RESOLVE_PROXY;
		goto cleanup;
	}


	if (!g_strcmp0 (proxy_uris[0], "direct://"))
		goto cleanup;

	*proxy_uri = soup_uri_new (proxy_uris[0]);

	if (!*proxy_uri)
		status = SOUP_STATUS_CANT_RESOLVE_PROXY;

cleanup:
	g_strfreev (proxy_uris);
	if (error)
		g_clear_error (&error);
	return status;
}
