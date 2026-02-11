collection_backend_claim_resource (ECollectionBackend *backend,
                                   const gchar *resource_id,
                                   GError **error)
{
	GHashTable *unclaimed_resources;
	ESource *source;

	g_mutex_lock (&backend->priv->unclaimed_resources_lock);

	unclaimed_resources = backend->priv->unclaimed_resources;
	source = g_hash_table_lookup (unclaimed_resources, resource_id);

	if (source != NULL) {
		g_object_ref (source);
		g_hash_table_remove (unclaimed_resources, resource_id);
	} else {
		GFile *file = collection_backend_new_user_file (backend);
		source = collection_backend_new_source (backend, file, error);
		g_object_unref (file);
	}

	g_mutex_unlock (&backend->priv->unclaimed_resources_lock);

	return source;
}
