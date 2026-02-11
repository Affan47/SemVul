imapx_idle_thread (gpointer data)
{
	CamelIMAPXServer *is = (CamelIMAPXServer *) data;
	GCancellable *cancellable;
	GError *local_error = NULL;

	cancellable = g_weak_ref_get (&is->priv->parser_cancellable);

	while (TRUE) {
		g_mutex_lock (&is->idle->start_watch_mutex);
		is->idle->start_watch_is_set = FALSE;
		g_mutex_unlock (&is->idle->start_watch_mutex);

		IDLE_LOCK (is->idle);

		while (TRUE) {
			CamelFolder *folder;
			gboolean new_messages_on_server;
			time_t dwelled;

			if (is->idle->state != IMAPX_IDLE_PENDING)
				break;

			if (is->idle->idle_exit)
				break;

			folder = g_weak_ref_get (&is->priv->select_folder);
			if (folder == NULL)
				break;

			dwelled = time (NULL) - is->idle->started;
			if (dwelled < IMAPX_IDLE_DWELL_TIME) {
				gulong seconds;

				g_object_unref (folder);

				IDLE_UNLOCK (is->idle);
				seconds = IMAPX_IDLE_DWELL_TIME - dwelled;
				g_usleep (seconds * G_USEC_PER_SEC);
				IDLE_LOCK (is->idle);

				continue;
			}

			IDLE_UNLOCK (is->idle);

			camel_imapx_server_idle (
				is, folder, cancellable, &local_error);

			new_messages_on_server =
				CAMEL_IMAPX_FOLDER (folder)->exists_on_server >
				camel_folder_summary_count (folder->summary);

			if (local_error == NULL &&
			    new_messages_on_server &&
			    imapx_is_command_queue_empty (is)) {
				imapx_server_fetch_new_messages (
					is, folder, TRUE, TRUE,
					cancellable, &local_error);
			}

			if (local_error != NULL) {
				e (is->tagprefix, "Caught exception in idle thread:  %s \n", local_error->message);

				g_clear_error (&local_error);
			}

			g_object_unref (folder);

			IDLE_LOCK (is->idle);
		}

		IDLE_UNLOCK (is->idle);

		g_mutex_lock (&is->idle->start_watch_mutex);
		while (!is->idle->start_watch_is_set)
			g_cond_wait (
				&is->idle->start_watch_cond,
				&is->idle->start_watch_mutex);
		g_mutex_unlock (&is->idle->start_watch_mutex);

		if (is->idle->idle_exit)
			break;
	}

	g_object_unref (cancellable);

	g_clear_error (&local_error);
	is->idle->idle_thread = NULL;
	return NULL;
}
