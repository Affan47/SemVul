pk_backend_socket_has_data_cb (GSocket *socket,
			       GIOCondition condition,
			       PkBackendJob *job)
{
	GError *error = NULL;
	gsize len;
	gchar buffer[1024];
	gboolean ret = TRUE;
	gint wrote = 0;
	PkBackendDummyJobData *job_data = pk_backend_job_get_user_data (job);


	if ((condition & G_IO_HUP) > 0) {
		pk_backend_job_error_code (job, PK_ERROR_ENUM_INTERNAL_ERROR,
					   "socket was disconnected");
		pk_backend_job_finished (job);
		ret = FALSE;
		goto out;
	}


	if ((condition & G_IO_IN) > 0) {
		len = g_socket_receive (socket, buffer, 1024, NULL, &error);
		if (error != NULL) {
			pk_backend_job_error_code (job, PK_ERROR_ENUM_INTERNAL_ERROR,
						   "failed to read: %s", error->message);
			pk_backend_job_finished (job);
			g_error_free (error);
			ret = FALSE;
			goto out;
		}
		if (len == 0)
			goto out;
		buffer[len] = '\0';
		if (g_strcmp0 (buffer, "pong\n") == 0) {

			pk_backend_job_message (job, PK_MESSAGE_ENUM_PARAMETER_INVALID, "%s", buffer);


			wrote = g_socket_send (job_data->socket, "invalid\n", 8, NULL, &error);
			if (error != NULL) {
				pk_backend_job_error_code (job, PK_ERROR_ENUM_INTERNAL_ERROR,
							   "failed to write to socket: %s", error->message);
				pk_backend_job_finished (job);
				g_error_free (error);
				goto out;
			}
			if (wrote != 8) {
				pk_backend_job_error_code (job, PK_ERROR_ENUM_INTERNAL_ERROR,
							   "failed to write, only %i bytes", wrote);
				pk_backend_job_finished (job);
				goto out;
			}
		} else if (g_strcmp0 (buffer, "you said to me: invalid\n") == 0) {
			g_debug ("ignoring invalid data (one is good)");
		} else {
			pk_backend_job_error_code (job, PK_ERROR_ENUM_INTERNAL_ERROR,
						   "unexpected data: %s", buffer);
			g_source_remove (job_data->signal_timeout);
			pk_backend_job_finished (job);
			goto out;
		}
	}
out:
	return ret;
}
