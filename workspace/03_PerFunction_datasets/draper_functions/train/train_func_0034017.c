test_refs_rename__propagate_eexists(void)
{
	git_reference *ref, *new_ref;

	cl_git_pass(git_reference_lookup(&ref, g_repo, packed_head_name));

	cl_assert_equal_i(GIT_EEXISTS, git_reference_rename(&new_ref, ref, packed_test_head_name, 0));

	git_reference_free(ref);
}
