book_backend_ews_ensure_connected (EBookBackendEws *bbews,
				   GCancellable *cancellable,
				   GError **perror)
{
	GError *local_error = NULL;

	g_return_val_if_fail (E_IS_BOOK_BACKEND_EWS (bbews), FALSE);

	PRIV_LOCK (bbews->priv);

	if (bbews->priv->cnc) {
		PRIV_UNLOCK (bbews->priv);
		return TRUE;
	}

	PRIV_UNLOCK (bbews->priv);

	e_backend_authenticate_sync (
		E_BACKEND (bbews),
		E_SOURCE_AUTHENTICATOR (bbews),
		cancellable, &local_error);

	if (!local_error)
		return TRUE;

	g_propagate_error (perror, local_error);

	return FALSE;
}
