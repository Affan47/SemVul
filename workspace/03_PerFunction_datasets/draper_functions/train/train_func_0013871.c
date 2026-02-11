pk_backend_supports_parallelization (PkBackend	*backend)
{
	g_return_val_if_fail (PK_IS_BACKEND (backend), FALSE);


	if (backend->priv->desc->supports_parallelization == NULL)
		return FALSE;
	return backend->priv->desc->supports_parallelization (backend);
}
