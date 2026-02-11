test_merge_trees_trivial__11(void)
{
	git_index *result;
	const git_index_entry *entry;

	cl_git_pass(merge_trivial(&result, "trivial-11", "trivial-11-branch", 0));

	cl_assert((entry = git_index_get_bypath(result, "modified-in-both.txt", 0)) == NULL);
	cl_assert(git_index_reuc_entrycount(result) == 0);

	cl_assert(merge_trivial_conflict_entrycount(result) == 3);
	cl_assert(entry = git_index_get_bypath(result, "modified-in-both.txt", 1));
	cl_assert(entry = git_index_get_bypath(result, "modified-in-both.txt", 2));
	cl_assert(entry = git_index_get_bypath(result, "modified-in-both.txt", 3));

	git_index_free(result);
}
