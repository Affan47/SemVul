do_request_with_cancel (SoupSession          *session,
			SoupURI              *base_uri,
			const char           *method,
			const char           *path,
			SoupTestRequestFlags  flags)
{
	SoupRequestHTTP *req;
	GInputStream *stream;
	SoupURI *uri;
	GError *error = NULL;
	GCancellable *cancellable;

	last_request_validated = last_request_hit_network = FALSE;
	cancelled_requests = 0;

	uri = soup_uri_new_with_base (base_uri, path);
	req = soup_session_request_http_uri (session, method, uri, NULL);
	soup_uri_free (uri);
	cancellable = flags & SOUP_TEST_REQUEST_CANCEL_CANCELLABLE ? g_cancellable_new () : NULL;
	stream = soup_test_request_send (SOUP_REQUEST (req), cancellable, flags, &error);
	if (stream) {
		debug_printf (1, "    could not cancel the request\n");
		g_object_unref (stream);
		g_object_unref (req);
		return;
	}

	g_clear_object (&cancellable);
	g_clear_object (&stream);
	g_clear_object (&req);

	soup_cache_flush ((SoupCache *)soup_session_get_feature (session, SOUP_TYPE_CACHE));
}
