odb_free(git_odb *db)
{
	size_t i;

	for (i = 0; i < db->backends.length; ++i) {
		backend_internal *internal = git_vector_get(&db->backends, i);
		git_odb_backend *backend = internal->backend;

		if (backend->free) backend->free(backend);
		else git__free(backend);

		git__free(internal);
	}

	git_vector_free(&db->backends);
	git_cache_free(&db->own_cache);
	git__free(db);
}
