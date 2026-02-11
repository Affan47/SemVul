test_query_standard_feed_error (gconstpointer service)
{
	GDataFeed *feed;
	GError *error = NULL;
	gulong handler_id;
	guint i;

	if (gdata_mock_server_get_enable_logging (mock_server) == TRUE) {
		g_test_message ("Ignoring test due to logging being enabled.");
		return;
	} else if (gdata_mock_server_get_enable_online (mock_server) == TRUE) {
		g_test_message ("Ignoring test due to running online and test not being reproducible.");
		return;
	}

	for (i = 0; i < G_N_ELEMENTS (query_standard_feed_errors); i++) {
		const GDataTestRequestErrorData *data = &query_standard_feed_errors[i];

		handler_id = g_signal_connect (mock_server, "handle-message", (GCallback) gdata_test_mock_server_handle_message_error, (gpointer) data);
		gdata_test_mock_server_run (mock_server);


		feed = gdata_youtube_service_query_standard_feed (GDATA_YOUTUBE_SERVICE (service), GDATA_YOUTUBE_TOP_RATED_FEED, NULL, NULL, NULL, NULL, &error);
		g_assert_error (error, data->error_domain_func (), data->error_code);
		g_assert (feed == NULL);
		g_clear_error (&error);

		gdata_mock_server_stop (mock_server);
		g_signal_handler_disconnect (mock_server, handler_id);
	}
}
