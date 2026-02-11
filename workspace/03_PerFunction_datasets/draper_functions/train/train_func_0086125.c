collection_backend_constructed (GObject *object)
{
	ECollectionBackend *backend;
	ESourceRegistryServer *server;
	ESource *source;
	GNode *node;
	const gchar *collection_uid;
	const gchar *user_cache_dir;
	gulong handler_id;

	backend = E_COLLECTION_BACKEND (object);


	G_OBJECT_CLASS (e_collection_backend_parent_class)->
		constructed (object);

	source = e_backend_get_source (E_BACKEND (backend));


	user_cache_dir = e_get_user_cache_dir ();
	collection_uid = e_source_get_uid (source);
	backend->priv->cache_dir = g_build_filename (
		user_cache_dir, "sources", collection_uid, NULL);
	g_mkdir_with_parents (backend->priv->cache_dir, 0700);


	collection_backend_load_resources (backend);


	node = e_server_side_source_get_node (E_SERVER_SIDE_SOURCE (source));
	node = g_node_first_child (node);

	while (node != NULL) {
		ESource *child = E_SOURCE (node->data);
		g_signal_emit (backend, signals[CHILD_ADDED], 0, child);
		node = g_node_next_sibling (node);
	}


	server = e_collection_backend_ref_server (backend);

	handler_id = g_signal_connect (
		server, "source-added",
		G_CALLBACK (collection_backend_source_added_cb), backend);

	backend->priv->source_added_handler_id = handler_id;

	handler_id = g_signal_connect (
		server, "source-removed",
		G_CALLBACK (collection_backend_source_removed_cb), backend);

	backend->priv->source_removed_handler_id = handler_id;

	g_object_unref (server);


	g_idle_add_full (
		G_PRIORITY_LOW,
		collection_backend_populate_idle_cb,
		g_object_ref (backend),
		(GDestroyNotify) g_object_unref);
}
