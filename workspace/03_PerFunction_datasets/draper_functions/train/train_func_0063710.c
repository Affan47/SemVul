e_collection_backend_dup_resource_id (ECollectionBackend *backend,
                                      ESource *child_source)
{
	ECollectionBackend *backend_for_child_source;
	ECollectionBackendClass *class;
	ESourceRegistryServer *server;
	gboolean child_is_ours = FALSE;

	g_return_val_if_fail (E_IS_COLLECTION_BACKEND (backend), NULL);
	g_return_val_if_fail (E_IS_SOURCE (child_source), NULL);

	class = E_COLLECTION_BACKEND_GET_CLASS (backend);
	g_return_val_if_fail (class->dup_resource_id != NULL, NULL);


	server = e_collection_backend_ref_server (backend);
	backend_for_child_source =
		e_source_registry_server_ref_backend (server, child_source);
	g_object_unref (server);

	if (backend_for_child_source != NULL) {
		child_is_ours = (backend_for_child_source == backend);
		g_object_unref (backend_for_child_source);
	}

	if (!child_is_ours)
		return NULL;

	return class->dup_resource_id (backend, child_source);
}
