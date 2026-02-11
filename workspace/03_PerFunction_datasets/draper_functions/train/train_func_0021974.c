pk_backend_reset_job (PkBackend *backend, PkBackendJob *job)
{
	g_return_if_fail (PK_IS_BACKEND (backend));

	if (!pk_backend_job_get_started (job)) {
		g_warning ("trying to reset job, but never started it before");
		return;
	}


	if (backend->priv->desc->job_reset != NULL) {
		backend->priv->desc->job_reset (backend, job);
	} else {
		if (backend->priv->desc->job_stop != NULL)
			backend->priv->desc->job_stop (backend, job);
		if (backend->priv->desc->job_start != NULL)
			backend->priv->desc->job_start (backend, job);
	}


	pk_backend_job_reset (job);
}
