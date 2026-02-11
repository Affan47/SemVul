test_submodule_lookup__lookup_even_with_missing_index(void)
{
	git_index *idx;


	cl_git_pass(git_index_new(&idx));
	git_repository_set_index(g_repo, idx);
	git_index_free(idx);

	test_submodule_lookup__simple_lookup();
}
