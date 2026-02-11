git_sortedcache_new(
	git_sortedcache **out,
	size_t item_path_offset,
	git_sortedcache_free_item_fn free_item,
	void *free_item_payload,
	git_vector_cmp item_cmp,
	const char *path)
{
	git_sortedcache *sc;
	size_t pathlen;

	pathlen = path ? strlen(path) : 0;

	sc = git__calloc(sizeof(git_sortedcache) + pathlen + 1, 1);
	GITERR_CHECK_ALLOC(sc);

	if (git_pool_init(&sc->pool, 1, 0) < 0 ||
		git_vector_init(&sc->items, 4, item_cmp) < 0 ||
		git_strmap_alloc(&sc->map) < 0)
		goto fail;

	if (git_rwlock_init(&sc->lock)) {
		giterr_set(GITERR_OS, "Failed to initialize lock");
		goto fail;
	}

	sc->item_path_offset  = item_path_offset;
	sc->free_item         = free_item;
	sc->free_item_payload = free_item_payload;
	GIT_REFCOUNT_INC(sc);
	if (pathlen)
		memcpy(sc->path, path, pathlen);

	*out = sc;
	return 0;

fail:
	git_strmap_free(sc->map);
	git_vector_free(&sc->items);
	git_pool_clear(&sc->pool);
	git__free(sc);
	return -1;
}
