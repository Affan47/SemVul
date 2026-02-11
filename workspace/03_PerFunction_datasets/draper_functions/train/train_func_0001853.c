soup_session_init (SoupSession *session)
{
	SoupSessionPrivate *priv = SOUP_SESSION_GET_PRIVATE (session);
	SoupAuthManager *auth_manager;

	priv->session = session;

	priv->queue = soup_message_queue_new (session);

	g_mutex_init (&priv->conn_lock);
	g_cond_init (&priv->conn_cond);
	priv->http_hosts = g_hash_table_new_full (soup_host_uri_hash,
						  soup_host_uri_equal,
						  NULL, (GDestroyNotify)free_host);
	priv->https_hosts = g_hash_table_new_full (soup_host_uri_hash,
						   soup_host_uri_equal,
						   NULL, (GDestroyNotify)free_host);
	priv->conns = g_hash_table_new (NULL, NULL);

	priv->max_conns = SOUP_SESSION_MAX_CONNS_DEFAULT;
	priv->max_conns_per_host = SOUP_SESSION_MAX_CONNS_PER_HOST_DEFAULT;

	priv->features_cache = g_hash_table_new (NULL, NULL);

	auth_manager = g_object_new (SOUP_TYPE_AUTH_MANAGER, NULL);
	g_signal_connect (auth_manager, "authenticate",
			  G_CALLBACK (auth_manager_authenticate), session);
	soup_session_feature_add_feature (SOUP_SESSION_FEATURE (auth_manager),
					  SOUP_TYPE_AUTH_BASIC);
	soup_session_feature_add_feature (SOUP_SESSION_FEATURE (auth_manager),
					  SOUP_TYPE_AUTH_DIGEST);
	soup_session_add_feature (session, SOUP_SESSION_FEATURE (auth_manager));
	g_object_unref (auth_manager);


	priv->resolver = g_resolver_get_default ();

	priv->ssl_strict = TRUE;

	priv->http_aliases = g_new (char *, 2);
	priv->http_aliases[0] = (char *)g_intern_string ("*");
	priv->http_aliases[1] = NULL;

	priv->request_types = g_hash_table_new (soup_str_case_hash,
						soup_str_case_equal);
	soup_session_add_feature_by_type (session, SOUP_TYPE_REQUEST_HTTP);
	soup_session_add_feature_by_type (session, SOUP_TYPE_REQUEST_FILE);
	soup_session_add_feature_by_type (session, SOUP_TYPE_REQUEST_DATA);
}
