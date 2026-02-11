gdata_download_stream_constructor (GType type, guint n_construct_params, GObjectConstructParam *construct_params)
{
	GDataDownloadStreamPrivate *priv;
	GDataServiceClass *klass;
	GObject *object;
	SoupURI *_uri;


	object = G_OBJECT_CLASS (gdata_download_stream_parent_class)->constructor (type, n_construct_params, construct_params);
	priv = GDATA_DOWNLOAD_STREAM (object)->priv;


	priv->network_cancellable = g_cancellable_new ();


	if (priv->cancellable == NULL)
		priv->cancellable = g_cancellable_new ();
	g_cancellable_connect (priv->cancellable, (GCallback) cancellable_cancel_cb, priv->network_cancellable, NULL);


	_uri = soup_uri_new (priv->download_uri);
	soup_uri_set_port (_uri, _gdata_service_get_https_port ());
	priv->message = soup_message_new_from_uri (SOUP_METHOD_GET, _uri);
	soup_uri_free (_uri);


	klass = GDATA_SERVICE_GET_CLASS (priv->service);
	if (klass->append_query_headers != NULL) {
		klass->append_query_headers (priv->service, priv->authorization_domain, priv->message);
	}


	soup_message_body_set_accumulate (priv->message->request_body, FALSE);


	return object;
}
