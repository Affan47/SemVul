camel_msgport_push (CamelMsgPort *msgport,
                    CamelMsg *msg)
{
	gint fd;
	PRFileDesc *prfd;

	g_return_if_fail (msgport != NULL);
	g_return_if_fail (msg != NULL);

	g_async_queue_lock (msgport->queue);

	msg->flags = 0;

	fd = msgport->pipe[1];
	while (fd >= 0) {
		if (MP_WRITE (fd, "E", 1) > 0) {
			msg->flags |= MSG_FLAG_SYNC_WITH_PIPE;
			break;
		} else if (!MP_IS_STATUS_INTR ()) {
			g_warning (
				"%s: Failed to write to pipe: %s",
				G_STRFUNC, g_strerror (errno));
			break;
		}
	}

	prfd = msgport->prpipe[1];
	while (prfd != NULL) {
		if (PR_Write (prfd, "E", 1) > 0) {
			msg->flags |= MSG_FLAG_SYNC_WITH_PR_PIPE;
			break;
		} else if (PR_GetError () != PR_PENDING_INTERRUPT_ERROR) {
			gchar *text = g_alloca (PR_GetErrorTextLength ());
			PR_GetErrorText (text);
			g_warning (
				"%s: Failed to write to NSPR pipe: %s",
				G_STRFUNC, text);
			break;
		}
	}

	g_async_queue_push_unlocked (msgport->queue, msg);
	g_async_queue_unlock (msgport->queue);
}
