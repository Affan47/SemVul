n_tickle_on_success(xmmsv_t *val, void *connection)
{
	xmmsc_result_t     *res2;
	xmmsc_connection_t *conn = (xmmsc_connection_t *)connection;
	char const         *xerr;

	if (xmmsv_get_error(val, &xerr)) {
		fprintf(stderr, "Couldn't advance in playlist: %s\n", xerr);
		connection_error = ERROR_ADVANCE;
	} else {
		res2 = xmmsc_playback_tickle(conn);
		xmmsc_result_notifier_set(res2, n_check_for_error,
	                              (gpointer)ERROR_CONNECTION);
		xmmsc_result_unref(res2);
	}
	return FALSE;
}
