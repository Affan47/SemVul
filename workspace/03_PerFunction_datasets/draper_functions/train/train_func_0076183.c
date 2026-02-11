ews_backend_sync_deleted_folders (EEwsBackend *backend,
                                  GSList *list)
{
	ECollectionBackend *collection_backend;
	ESourceRegistryServer *server;
	GSList *link;

	collection_backend = E_COLLECTION_BACKEND (backend);
	server = e_collection_backend_ref_server (collection_backend);

	for (link = list; link != NULL; link = g_slist_next (link)) {
		const gchar *folder_id = link->data;
		ESource *source = NULL;

		if (folder_id != NULL)
			source = ews_backend_folders_lookup (
				backend, folder_id);

		if (source == NULL)
			continue;


		e_source_registry_server_remove_source (server, source);

		g_object_unref (source);
	}

	g_object_unref (server);
}
