packfile_load__cb(void *_data, git_buf *path)
{
	struct pack_backend *backend = (struct pack_backend *)_data;
	struct git_pack_file *pack;
	int error;
	size_t i;

	if (git__suffixcmp(path->ptr, ".idx") != 0)
		return 0;

	for (i = 0; i < backend->packs.length; ++i) {
		struct git_pack_file *p = git_vector_get(&backend->packs, i);
		if (memcmp(p->pack_name, git_buf_cstr(path), git_buf_len(path) - strlen(".idx")) == 0)
			return 0;
	}

	error = git_packfile_alloc(&pack, path->ptr);
	if (error == GIT_ENOTFOUND)

		return 0;
	else if (error < 0)
		return error;

	return git_vector_insert(&backend->packs, pack);
}
