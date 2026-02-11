brasero_checksum_image_start (BraseroJob *job,
			      GError **error)
{
	BraseroChecksumImagePrivate *priv;
	GError *thread_error = NULL;
	BraseroJobAction action;

	brasero_job_get_action (job, &action);
	if (action == BRASERO_JOB_ACTION_SIZE) {

		if (brasero_job_get_fd_in (job, NULL) == BRASERO_BURN_OK)
			return BRASERO_BURN_NOT_SUPPORTED;


		brasero_job_set_output_size_for_current_track (job, 0, 0);
		return BRASERO_BURN_NOT_RUNNING;
	}


	priv = BRASERO_CHECKSUM_IMAGE_PRIVATE (job);
	g_mutex_lock (priv->mutex);
	priv->thread = g_thread_create (brasero_checksum_image_thread,
					BRASERO_CHECKSUM_IMAGE (job),
					FALSE,
					&thread_error);
	g_mutex_unlock (priv->mutex);


	if (thread_error) {
		g_propagate_error (error, thread_error);
		return BRASERO_BURN_ERR;
	}

	return BRASERO_BURN_OK;
}
