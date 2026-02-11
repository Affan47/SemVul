ews_backend_populate (ECollectionBackend *backend)
{
	ESource *source;
	EEwsBackend *ews_backend = E_EWS_BACKEND (backend);

	source = e_backend_get_source (E_BACKEND (backend));

	ews_backend->priv->need_update_folders = TRUE;


	if (!e_source_get_enabled (source))
		return;


	e_ews_backend_sync_folders (ews_backend, NULL, NULL, NULL);

	ews_backend_add_gal_source (ews_backend);
}
