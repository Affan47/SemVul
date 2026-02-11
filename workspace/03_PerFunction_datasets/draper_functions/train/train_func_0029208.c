test_merge_trees_trivial__3alt(void)
{
	git_index *result;
	const git_index_entry *entry;

	cl_git_pass(merge_trivial(&result, "trivial-3alt", "trivial-3alt-branch", 0));

	cl_assert(entry = git_index_get_bypath(result, "new-in-3alt.txt", 0));
	cl_assert(git_index_reuc_entrycount(result) == 0);
	cl_assert(merge_trivial_conflict_entrycount(result) == 0);

	git_index_free(result);
}
