git_index_read_tree(git_index *index, const git_tree *tree)
{
	int error = 0;
	git_vector entries = GIT_VECTOR_INIT;
	read_tree_data data;

	git_vector_set_cmp(&entries, index->entries._cmp);

	data.old_entries = &index->entries;
	data.new_entries = &entries;
	data.entry_cmp   = index->entries_search;

	index->tree = NULL;
	git_pool_clear(&index->tree_pool);

	if (index_sort_if_needed(index, true) < 0)
		return -1;

	error = git_tree_walk(tree, GIT_TREEWALK_POST, read_tree_cb, &data);

	if (!error) {
		git_vector_sort(&entries);

		if ((error = git_index_clear(index)) < 0)
			;
		else if (git_mutex_lock(&index->lock) < 0) {
			giterr_set(GITERR_OS, "Unable to acquire index lock");
			error = -1;
		} else {
			git_vector_swap(&entries, &index->entries);
			git_mutex_unlock(&index->lock);
		}
	}

	git_vector_free(&entries);
	if (error < 0)
		return error;

	error = git_tree_cache_read_tree(&index->tree, tree, &index->tree_pool);

	return error;
}
