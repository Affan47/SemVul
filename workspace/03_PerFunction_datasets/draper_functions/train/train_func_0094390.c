pack_backend__alloc(struct pack_backend **out, size_t initial_size)
{
	struct pack_backend *backend = git__calloc(1, sizeof(struct pack_backend));
	GITERR_CHECK_ALLOC(backend);

	if (git_vector_init(&backend->packs, initial_size, packfile_sort__cb) < 0) {
		git__free(backend);
		return -1;
	}

	backend->parent.version = GIT_ODB_BACKEND_VERSION;

	backend->parent.read = &pack_backend__read;
	backend->parent.read_prefix = &pack_backend__read_prefix;
	backend->parent.read_header = &pack_backend__read_header;
	backend->parent.exists = &pack_backend__exists;
	backend->parent.exists_prefix = &pack_backend__exists_prefix;
	backend->parent.refresh = &pack_backend__refresh;
	backend->parent.foreach = &pack_backend__foreach;
	backend->parent.writepack = &pack_backend__writepack;
	backend->parent.free = &pack_backend__free;

	*out = backend;
	return 0;
}
