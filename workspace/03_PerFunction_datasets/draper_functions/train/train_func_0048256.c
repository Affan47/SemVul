test_refs_read__loose_first(void)
{

	git_reference *reference;

	cl_git_pass(git_reference_lookup(&reference, g_repo, packed_head_name));
	git_reference_free(reference);
	cl_git_pass(git_reference_lookup(&reference, g_repo, packed_test_head_name));
	cl_assert(git_reference_type(reference) & GIT_REF_OID);
	cl_assert(git_reference_is_packed(reference) == 0);
	cl_assert_equal_s(reference->name, packed_test_head_name);

	git_reference_free(reference);
}
