do_property_tests (void)
{
	SoupSession *session;
	GProxyResolver *proxy_resolver, *default_proxy_resolver;
	GTlsDatabase *tlsdb, *default_tlsdb;
	SoupURI *uri;

	debug_printf (1, "\nTesting session init properties\n");

	default_proxy_resolver = g_proxy_resolver_get_default ();
	default_tlsdb = g_tls_backend_get_default_database (g_tls_backend_get_default ());


	session = g_object_new (SOUP_TYPE_SESSION,
				NULL);
	test_session_properties ("Base plain session", session,
				 default_proxy_resolver, default_tlsdb);
	g_object_unref (session);

	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_PROXY_RESOLVER, NULL,
				NULL);
	test_session_properties ("Session with NULL :proxy-resolver", session,
				 NULL, default_tlsdb);
	g_object_unref (session);

	proxy_resolver = g_simple_proxy_resolver_new (NULL, NULL);
	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_PROXY_RESOLVER, proxy_resolver,
				NULL);
	test_session_properties ("Session with non-NULL :proxy-resolver", session,
				 proxy_resolver, default_tlsdb);
	g_object_unref (proxy_resolver);
	g_object_unref (session);

	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_PROXY_URI, NULL,
				NULL);
	test_session_properties ("Session with NULL :proxy-uri", session,
				 NULL, default_tlsdb);
	g_object_unref (session);

	uri = soup_uri_new ("http://example.com/");
	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_PROXY_URI, uri,
				NULL);
	g_object_get (G_OBJECT (session),
		      SOUP_SESSION_PROXY_RESOLVER, &proxy_resolver,
		      NULL);
	test_session_properties ("Session with non-NULL :proxy-uri", session,
				 proxy_resolver, default_tlsdb);
	if (!G_IS_SIMPLE_PROXY_RESOLVER (proxy_resolver)) {
		debug_printf (1, "  proxy resolver had wrong type (%s)\n",
			      G_OBJECT_TYPE_NAME (proxy_resolver));
		errors++;
	}
	g_object_unref (proxy_resolver);
	g_object_unref (session);
	soup_uri_free (uri);

	G_GNUC_BEGIN_IGNORE_DEPRECATIONS;
	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_REMOVE_FEATURE_BY_TYPE, SOUP_TYPE_PROXY_URI_RESOLVER,
				NULL);
	test_session_properties ("Session with removed proxy resolver feature", session,
				 NULL, default_tlsdb);
	g_object_unref (session);
	G_GNUC_END_IGNORE_DEPRECATIONS;

	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_TLS_DATABASE, NULL,
				NULL);
	test_session_properties ("Session with NULL :tls-database", session,
				 default_proxy_resolver, NULL);
	g_object_unref (session);

	tlsdb = g_tls_file_database_new (SRCDIR "/test-cert.pem", NULL);
	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_TLS_DATABASE, tlsdb,
				NULL);
	test_session_properties ("Session with non-NULL :tls-database", session,
				 default_proxy_resolver, tlsdb);
	g_object_unref (tlsdb);
	g_object_unref (session);

	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_SSL_USE_SYSTEM_CA_FILE, FALSE,
				NULL);
	test_session_properties ("Session with :ssl-use-system-ca-file FALSE", session,
				 default_proxy_resolver, NULL);
	g_object_unref (session);

	session = g_object_new (SOUP_TYPE_SESSION,
				SOUP_SESSION_SSL_USE_SYSTEM_CA_FILE, TRUE,
				NULL);
	test_session_properties ("Session with :ssl-use-system-ca-file TRUE", session,
				 default_proxy_resolver, default_tlsdb);
	g_object_unref (session);
}
