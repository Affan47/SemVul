get_proxy_uri_async (SoupProxyURIResolver  *resolver,
		     SoupURI		   *uri,
		     GMainContext	   *async_context,
		     GCancellable	   *cancellable,
		     SoupProxyURIResolverCallback callback,
		     gpointer		    user_data)
{
	SoupProxyResolverDefaultPrivate *priv = SOUP_PROXY_RESOLVER_DEFAULT_GET_PRIVATE (resolver);
	SoupAsyncData *async_data;
	char *uri_string;

	async_data = g_slice_new0 (SoupAsyncData);
	async_data->resolver = (SoupProxyURIResolver*) g_object_ref (resolver);
	async_data->cancellable = cancellable;
	async_data->callback = callback;
	async_data->user_data = user_data;

	uri_string = soup_uri_to_string (uri, FALSE);

	if (async_context)
		g_main_context_push_thread_default (async_context);

	g_proxy_resolver_lookup_async (priv->gproxy_resolver,
				       uri_string,
				       cancellable ? g_object_ref (cancellable) : NULL,
				       resolved_proxy,
				       async_data);

	if (async_context)
		g_main_context_pop_thread_default (async_context);

	g_free (uri_string);
}
