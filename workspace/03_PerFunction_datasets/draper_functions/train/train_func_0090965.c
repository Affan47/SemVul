iter_load_loose_paths(refdb_fs_backend *backend, refdb_fs_iter *iter)
{
	int error = 0;
	git_buf path = GIT_BUF_INIT;
	git_iterator *fsit = NULL;
	const git_index_entry *entry = NULL;

	if (!backend->path)
		return 0;

	if ((error = git_buf_printf(&path, "%s/refs", backend->path)) < 0 ||
		(error = git_iterator_for_filesystem(
			&fsit, path.ptr, backend->iterator_flags, NULL, NULL)) < 0) {
		git_buf_free(&path);
		return error;
	}

	error = git_buf_sets(&path, GIT_REFS_DIR);

	while (!error && !git_iterator_advance(&entry, fsit)) {
		const char *ref_name;
		struct packref *ref;
		char *ref_dup;

		git_buf_truncate(&path, strlen(GIT_REFS_DIR));
		git_buf_puts(&path, entry->path);
		ref_name = git_buf_cstr(&path);

		if (git__suffixcmp(ref_name, ".lock") == 0 ||
			(iter->glob && p_fnmatch(iter->glob, ref_name, 0) != 0))
			continue;

		git_sortedcache_rlock(backend->refcache);
		ref = git_sortedcache_lookup(backend->refcache, ref_name);
		if (ref)
			ref->flags |= PACKREF_SHADOWED;
		git_sortedcache_runlock(backend->refcache);

		ref_dup = git_pool_strdup(&iter->pool, ref_name);
		if (!ref_dup)
			error = -1;
		else
			error = git_vector_insert(&iter->loose, ref_dup);
	}

	git_iterator_free(fsit);
	git_buf_free(&path);

	return error;
}
