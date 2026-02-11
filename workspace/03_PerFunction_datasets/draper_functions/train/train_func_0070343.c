book_backend_file_open_sync (EBookBackend *backend,
                             GCancellable *cancellable,
                             GError **error)
{
	EBookBackendFile *bf = E_BOOK_BACKEND_FILE (backend);
	ESource          *source;
	ESourceRevisionGuards *guards;

	source = e_backend_get_source (E_BACKEND (backend));

	g_type_ensure (E_TYPE_SOURCE_REVISION_GUARDS);
	guards = e_source_get_extension (source, E_SOURCE_EXTENSION_REVISION_GUARDS);

	bf->priv->revision_guards = e_source_revision_guards_get_enabled (guards);

	g_rw_lock_writer_lock (&(bf->priv->lock));
	if (!bf->priv->revision) {
		e_book_backend_file_load_revision (bf);
		e_book_backend_notify_property_changed (E_BOOK_BACKEND (backend),
							BOOK_BACKEND_PROPERTY_REVISION,
							bf->priv->revision);
	}
	g_rw_lock_writer_unlock (&(bf->priv->lock));

	e_backend_set_online (E_BACKEND (backend), TRUE);
	e_book_backend_set_writable (E_BOOK_BACKEND (backend), TRUE);

	return TRUE;
}
