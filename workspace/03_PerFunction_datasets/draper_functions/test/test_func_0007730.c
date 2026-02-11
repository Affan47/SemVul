git_index_remove(git_index *index, const char *path, int stage)
{
	size_t position;
	int error;
	git_index_entry *entry;

	git_vector_sort(&index->entries);

	if (index_find(&position, index, path, stage) < 0) {
		giterr_set(GITERR_INDEX, "Index does not contain %s at stage %d",
			path, stage);
		return GIT_ENOTFOUND;
	}

	entry = git_vector_get(&index->entries, position);
	if (entry != NULL)
		git_tree_cache_invalidate_path(index->tree, entry->path);

	error = git_vector_remove(&index->entries, position);

	if (!error)
		index_entry_free(entry);

	return error;
}
