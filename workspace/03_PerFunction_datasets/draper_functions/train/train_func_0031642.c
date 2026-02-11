eog_job_dispose (GObject *object)
{
	EogJob *job;

	job = EOG_JOB (object);

	if (job->error) {
		g_error_free (job->error);
		job->error = NULL;
	}

	if (job->mutex) {
		g_mutex_clear (job->mutex);
		g_free (job->mutex);
	}

	(* G_OBJECT_CLASS (eog_job_parent_class)->dispose) (object);
}
