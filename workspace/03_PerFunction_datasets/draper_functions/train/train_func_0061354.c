test_index_conflicts__moved_to_reuc(void)
{
	git_index_entry *entry;
	size_t i;

	cl_assert(git_index_entrycount(repo_index) == 8);

	cl_git_mkfile("./mergedrepo/conflicts-one.txt", "new-file\n");

	cl_git_pass(git_index_add_from_workdir(repo_index, "conflicts-one.txt"));

	cl_assert(git_index_entrycount(repo_index) == 6);

	for (i = 0; i < git_index_entrycount(repo_index); i++) {
		cl_assert(entry = git_index_get_byindex(repo_index, i));

		if (strcmp(entry->path, "conflicts-one.txt") == 0)
			cl_assert(git_index_entry_stage(entry) == 0);
	}
}
