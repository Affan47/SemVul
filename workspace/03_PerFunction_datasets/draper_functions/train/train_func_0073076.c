ear_two_completed (GObject *source, GAsyncResult *result, gpointer loop)
{
	GError *error = NULL;

	debug_printf (2, "  Request 2 completed\n");
	if (soup_request_send_finish (SOUP_REQUEST (source), result, &error)) {
		debug_printf (1, "  Request 2 succeeded?\n");
		errors++;
	} else if (!g_error_matches (error, SOUP_HTTP_ERROR, SOUP_STATUS_CANCELLED)) {
		debug_printf (1, "  Unexpected error on Request 2: %s\n",
			      error->message);
		errors++;
	}
	g_clear_error (&error);

	g_main_loop_quit (loop);
}
