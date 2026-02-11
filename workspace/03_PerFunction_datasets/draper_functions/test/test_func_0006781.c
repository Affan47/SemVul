pk_backend_job_set_uid (PkBackendJob *job, guint uid)
{
	g_return_if_fail (PK_IS_BACKEND_JOB (job));

	job->priv->uid = uid;
	g_debug ("install uid now %i", job->priv->uid);
}
