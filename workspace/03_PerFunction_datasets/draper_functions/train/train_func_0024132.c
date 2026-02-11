test_refs_list__symbolic_only(void)
{

	git_strarray ref_list;

	cl_git_pass(git_reference_list(&ref_list, g_repo, GIT_REF_SYMBOLIC));
	cl_assert(ref_list.count == 0);

	git_strarray_free(&ref_list);
}
