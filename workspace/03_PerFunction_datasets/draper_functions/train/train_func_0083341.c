test_refs_listall__from_repository_with_no_trailing_newline(void)
{
	cl_git_pass(git_repository_open(&repo, cl_fixture("bad_tag.git")));
	cl_git_pass(git_reference_list(&ref_list, repo));

	cl_assert(ref_list.count > 0);

	git_strarray_free(&ref_list);
	git_repository_free(repo);
}
