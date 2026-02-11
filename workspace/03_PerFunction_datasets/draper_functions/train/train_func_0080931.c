close_async_ready (SoupMessage *msg, gpointer user_data)
{
	GTask *task = user_data;
	SoupClientInputStream *cistream = g_task_get_source_object (task);
	GError *error = NULL;

	if (!soup_message_io_run_until_finish (cistream->priv->msg, FALSE,
					       g_task_get_cancellable (task),
					       &error) &&
	    g_error_matches (error, G_IO_ERROR, G_IO_ERROR_WOULD_BLOCK)) {
		g_error_free (error);
		return TRUE;
	}

	soup_message_io_finished (cistream->priv->msg);

	if (error) {
		g_task_return_error (task, error);
		g_object_unref (task);
		return FALSE;
	}


	soup_add_idle (g_main_context_get_thread_default (),
		       idle_finish_close, task);
	return FALSE;
}
