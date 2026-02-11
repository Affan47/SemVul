git_refdb_backend_fs(
	git_refdb_backend **backend_out,
	git_repository *repository)
{
	int t = 0;
	git_buf path = GIT_BUF_INIT;
	refdb_fs_backend *backend;

	backend = git__calloc(1, sizeof(refdb_fs_backend));
	GITERR_CHECK_ALLOC(backend);

	backend->repo = repository;

	if (setup_namespace(&path, repository) < 0)
		goto fail;

	backend->path = git_buf_detach(&path);

	if (git_buf_joinpath(&path, backend->path, GIT_PACKEDREFS_FILE) < 0 ||
		git_sortedcache_new(
			&backend->refcache, offsetof(struct packref, name),
			NULL, NULL, packref_cmp, git_buf_cstr(&path)) < 0)
		goto fail;

	git_buf_free(&path);

	if (!git_repository__cvar(&t, backend->repo, GIT_CVAR_IGNORECASE) && t) {
		backend->iterator_flags |= GIT_ITERATOR_IGNORE_CASE;
		backend->direach_flags  |= GIT_PATH_DIR_IGNORE_CASE;
	}
	if (!git_repository__cvar(&t, backend->repo, GIT_CVAR_PRECOMPOSE) && t) {
		backend->iterator_flags |= GIT_ITERATOR_PRECOMPOSE_UNICODE;
		backend->direach_flags  |= GIT_PATH_DIR_PRECOMPOSE_UNICODE;
	}

	backend->parent.exists = &refdb_fs_backend__exists;
	backend->parent.lookup = &refdb_fs_backend__lookup;
	backend->parent.iterator = &refdb_fs_backend__iterator;
	backend->parent.write = &refdb_fs_backend__write;
	backend->parent.del = &refdb_fs_backend__delete;
	backend->parent.rename = &refdb_fs_backend__rename;
	backend->parent.compress = &refdb_fs_backend__compress;
	backend->parent.lock = &refdb_fs_backend__lock;
	backend->parent.unlock = &refdb_fs_backend__unlock;
	backend->parent.has_log = &refdb_reflog_fs__has_log;
	backend->parent.ensure_log = &refdb_reflog_fs__ensure_log;
	backend->parent.free = &refdb_fs_backend__free;
	backend->parent.reflog_read = &refdb_reflog_fs__read;
	backend->parent.reflog_write = &refdb_reflog_fs__write;
	backend->parent.reflog_rename = &refdb_reflog_fs__rename;
	backend->parent.reflog_delete = &refdb_reflog_fs__delete;

	*backend_out = (git_refdb_backend *)backend;
	return 0;

fail:
	git_buf_free(&path);
	git__free(backend->path);
	git__free(backend);
	return -1;
}
