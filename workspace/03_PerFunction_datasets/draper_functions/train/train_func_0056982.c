cancel_message_or_cancellable (CancelData *cancel_data)
{
	if (cancel_data->flags & SOUP_TEST_REQUEST_CANCEL_MESSAGE) {
		SoupRequest *req = cancel_data->req;
		SoupMessage *msg = soup_request_http_get_message (SOUP_REQUEST_HTTP (req));
		soup_session_cancel_message (soup_request_get_session (req), msg,
					     SOUP_STATUS_CANCELLED);
		g_object_unref (msg);
		g_object_unref (req);
	} else if (cancel_data->flags & SOUP_TEST_REQUEST_CANCEL_CANCELLABLE) {
		g_cancellable_cancel (cancel_data->cancellable);
		g_object_unref (cancel_data->cancellable);
	}
	g_slice_free (CancelData, cancel_data);
}
