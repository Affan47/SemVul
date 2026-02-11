pk_backend_refresh_cache (PkBackend *backend, PkBackendJob *job, gboolean force)
{
	PkBackendDummyJobData *job_data = pk_backend_job_get_user_data (job);
	job_data->progress_percentage = 0;


	priv->updated_gtkhtml = FALSE;
	priv->updated_kernel = FALSE;
	priv->updated_powertop = FALSE;

	pk_backend_job_set_allow_cancel (job, TRUE);
	pk_backend_job_set_status (job, PK_STATUS_ENUM_REFRESH_CACHE);


	if (priv->fake_db_locked) {
		pk_backend_job_error_code (job, PK_ERROR_ENUM_LOCK_REQUIRED,
						   "we require lock");
		pk_backend_job_finished (job);
		return;
	}


	priv->fake_db_locked = TRUE;
	pk_backend_job_set_locked (job, TRUE);

	pk_backend_job_thread_create (job, pk_backend_refresh_cache_thread, NULL, NULL);
}
