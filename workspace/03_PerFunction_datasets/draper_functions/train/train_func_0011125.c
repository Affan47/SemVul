backend_free(git_config_backend *_backend)
{
	diskfile_backend *backend = (diskfile_backend *)_backend;
	uint32_t i;

	if (backend == NULL)
		return;

	for (i = 0; i < git_array_size(backend->readers); i++) {
		struct reader *r = git_array_get(backend->readers, i);
		git__free(r->file_path);
	}
	git_array_clear(backend->readers);

	git__free(backend->file_path);
	refcounted_strmap_free(backend->header.values);
	git_mutex_free(&backend->header.values_mutex);
	git__free(backend);
}
