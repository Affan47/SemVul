submodule_cache_refresh_from_index(
	git_submodule_cache *cache, git_index *idx)
{
	int error;
	git_iterator *i;
	const git_index_entry *entry;

	if ((error = git_iterator_for_index(&i, idx, 0, NULL, NULL)) < 0)
		return error;

	while (!(error = git_iterator_advance(&entry, i))) {
		khiter_t pos = git_strmap_lookup_index(cache->submodules, entry->path);
		git_submodule *sm;

		if (git_strmap_valid_index(cache->submodules, pos)) {
			sm = git_strmap_value_at(cache->submodules, pos);

			if (S_ISGITLINK(entry->mode))
				submodule_update_from_index_entry(sm, entry);
			else
				sm->flags |= GIT_SUBMODULE_STATUS__INDEX_NOT_SUBMODULE;
		} else if (S_ISGITLINK(entry->mode)) {
			if (!submodule_get(&sm, cache, entry->path, NULL)) {
				submodule_update_from_index_entry(sm, entry);
				git_submodule_free(sm);
			}
		}
	}

	if (error == GIT_ITEROVER)
		error = 0;

	git_iterator_free(i);

	return error;
}
