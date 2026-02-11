_gdata_service_actually_send_message (SoupSession *session, SoupMessage *message, GCancellable *cancellable, GError **error)
{
	MessageData data;
	gulong cancel_signal = 0, request_queued_signal = 0;


	g_object_ref (session);
	g_object_ref (message);


	if (cancellable != NULL) {
		g_mutex_init (&(data.mutex));
		data.session = session;
		data.message = message;

		cancel_signal = g_cancellable_connect (cancellable, (GCallback) message_cancel_cb, &data, NULL);
		request_queued_signal = g_signal_connect (session, "request-queued", (GCallback) message_request_queued_cb, &data);


		g_mutex_lock (&(data.mutex));
	}


	if (cancellable == NULL || g_cancellable_is_cancelled (cancellable) == FALSE)
		soup_session_send_message (session, message);
	else
		soup_message_set_status (message, SOUP_STATUS_CANCELLED);


	if (cancellable != NULL) {
		g_signal_handler_disconnect (session, request_queued_signal);

		if (cancel_signal != 0)
			g_cancellable_disconnect (cancellable, cancel_signal);

		g_mutex_clear (&(data.mutex));
	}


	g_assert (message->status_code != SOUP_STATUS_NONE);

	if (message->status_code == SOUP_STATUS_CANCELLED ||
	    ((message->status_code == SOUP_STATUS_IO_ERROR || message->status_code == SOUP_STATUS_SSL_FAILED ||
	      message->status_code == SOUP_STATUS_CANT_CONNECT || message->status_code == SOUP_STATUS_CANT_RESOLVE) &&
	     cancellable != NULL && g_cancellable_is_cancelled (cancellable) == TRUE)) {


		GCancellable *error_cancellable = g_cancellable_new ();
		g_cancellable_cancel (error_cancellable);
		g_assert (g_cancellable_set_error_if_cancelled (error_cancellable, error) == TRUE);
		g_object_unref (error_cancellable);


		soup_message_set_status (message, SOUP_STATUS_CANCELLED);
	}


	g_object_unref (message);
	g_object_unref (session);
}
