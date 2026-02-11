test_merge_trees_trivial__14(void)
{
	git_index *result;
	const git_index_entry *entry;
	git_oid expected_oid;

	cl_git_pass(merge_trivial(&result, "trivial-14", "trivial-14-branch", 0));

	cl_assert(entry = git_index_get_bypath(result, "modified-in-14-branch.txt", 0));
	cl_git_pass(git_oid_fromstr(&expected_oid, "26153a3ff3649b6c2bb652d3f06878c6e0a172f9"));
	cl_assert(git_oid_cmp(&entry->oid, &expected_oid) == 0);

	cl_assert(git_index_reuc_entrycount(result) == 0);
	cl_assert(merge_trivial_conflict_entrycount(result) == 0);

	git_index_free(result);
}
