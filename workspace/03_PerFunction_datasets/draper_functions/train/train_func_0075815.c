git_index_reuc_remove(git_index *index, int position)
{
	int error;
	git_index_reuc_entry *reuc;

	git_vector_sort(&index->reuc);

	reuc = git_vector_get(&index->reuc, position);
	error = git_vector_remove(&index->reuc, (unsigned int)position);

	if (!error)
		index_entry_reuc_free(reuc);

	return error;
}
