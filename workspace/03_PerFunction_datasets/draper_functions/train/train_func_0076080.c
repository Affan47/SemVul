pk_backend_get_mime_types (PkBackend *backend)
{
	g_return_val_if_fail (PK_IS_BACKEND (backend), NULL);
	g_return_val_if_fail (backend->priv->loaded, NULL);


	if (backend->priv->desc->get_mime_types == NULL)
		return g_new0 (gchar *, 1);
	return backend->priv->desc->get_mime_types (backend);
}
