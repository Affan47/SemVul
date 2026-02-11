do_cancel_while_reading_req_test_for_session (SoupSession *session,
					      guint flags)
{
	SoupRequest *req;
	SoupURI *uri;
	GCancellable *cancellable;
	GError *error = NULL;

	uri = soup_uri_new_with_base (base_uri, "/slow");
	req = soup_session_request_uri (session, uri, NULL);
	soup_uri_free (uri);

	cancellable = g_cancellable_new ();
	soup_test_request_send (req, cancellable, flags, &error);
	if (!error) {
		debug_printf (1, "  Request succeeded?\n");
		errors++;
	} else if (!g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
		debug_printf (1, "  Unexpected error: %s\n",
			      error->message);
		errors++;
	}
	g_clear_error (&error);

	g_object_unref (req);
	g_object_unref (cancellable);
}
