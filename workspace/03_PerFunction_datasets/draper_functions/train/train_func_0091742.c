merge_index_insert_unmodified(
	git_merge_diff_list *diff_list,
	const git_index_entry *tree_items[3])
{
	int error = 0;
	git_index_entry *entry;

	entry = git_pool_malloc(&diff_list->pool, sizeof(git_index_entry));
	GITERR_CHECK_ALLOC(entry);

	if ((error = index_entry_dup(entry, &diff_list->pool, tree_items[0])) >= 0)
		error = git_vector_insert(&diff_list->staged, entry);

	return error;
}
