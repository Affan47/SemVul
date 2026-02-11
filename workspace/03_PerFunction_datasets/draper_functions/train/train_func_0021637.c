ews_connection_scheduled_cb (gpointer user_data)
{
	EwsScheduleData *sd = user_data;

	g_return_val_if_fail (sd != NULL, FALSE);

	switch (sd->op) {
	case EWS_SCHEDULE_OP_QUEUE_MESSAGE:
		soup_session_queue_message (
			sd->cnc->priv->soup_session, sd->message,
			sd->queue_callback, sd->queue_user_data);
		break;
	case EWS_SCHEDULE_OP_CANCEL:
		soup_session_cancel_message (sd->cnc->priv->soup_session, sd->message, SOUP_STATUS_CANCELLED);
		break;
	case EWS_SCHEDULE_OP_ABORT:
		soup_session_abort (sd->cnc->priv->soup_session);
		break;
	}

	if (sd->message)
		g_object_unref (sd->message);

	e_ews_connection_utils_unref_in_thread (sd->cnc);
	g_free (sd);

	return FALSE;
}
