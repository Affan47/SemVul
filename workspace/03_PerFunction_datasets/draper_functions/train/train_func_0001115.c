test_refs_overwrite__object_id(void)
{

	git_reference *ref;
	git_oid id;

	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_master_name));
	cl_assert(git_reference_type(ref) & GIT_REF_OID);
	git_oid_cpy(&id, git_reference_target(ref));
	git_reference_free(ref);


	cl_git_pass(git_reference_create(&ref, g_repo, ref_name, &id, 0, NULL, NULL));
	git_reference_free(ref);

	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_test_name));
	cl_assert(git_reference_type(ref) & GIT_REF_OID);
	git_oid_cpy(&id, git_reference_target(ref));
	git_reference_free(ref);


	cl_git_fail(git_reference_create(&ref, g_repo, ref_name, &id, 0, NULL, NULL));
	cl_git_pass(git_reference_create(&ref, g_repo, ref_name, &id, 1, NULL, NULL));
	git_reference_free(ref);


	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_name));
	cl_assert_equal_oid(&id, git_reference_target(ref));

	git_reference_free(ref);
}
