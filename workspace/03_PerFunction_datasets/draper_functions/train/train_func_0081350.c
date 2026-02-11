pk_backend_spawn_helper (PkBackendSpawn *backend_spawn,
			 PkBackendJob *job,
			 const gchar *first_element, ...)
{
	gboolean ret = TRUE;
	va_list args;

	g_return_val_if_fail (PK_IS_BACKEND_SPAWN (backend_spawn), FALSE);
	g_return_val_if_fail (first_element != NULL, FALSE);
	g_return_val_if_fail (backend_spawn->priv->name != NULL, FALSE);


	backend_spawn->priv->is_busy = TRUE;
	backend_spawn->priv->job = job;
	backend_spawn->priv->backend = g_object_ref (pk_backend_job_get_backend (job));


	if (backend_spawn->priv->kill_id > 0) {
		g_source_remove (backend_spawn->priv->kill_id);
		backend_spawn->priv->kill_id = 0;
	}


	va_start (args, first_element);
	ret = pk_backend_spawn_helper_va_list (backend_spawn, job, first_element, &args);
	va_end (args);

	return ret;
}
