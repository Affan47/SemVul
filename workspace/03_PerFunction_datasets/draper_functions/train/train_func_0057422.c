eog_job_load_run (EogJob *job)
{
	g_return_if_fail (EOG_IS_JOB_LOAD (job));

	if (job->error) {
	        g_error_free (job->error);
		job->error = NULL;
	}

	eog_image_load (EOG_IMAGE (EOG_JOB_LOAD (job)->image),
			EOG_JOB_LOAD (job)->data,
			job,
			&job->error);

	job->finished = TRUE;
}
