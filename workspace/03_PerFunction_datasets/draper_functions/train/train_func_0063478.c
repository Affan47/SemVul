test_refs_read__master_then_head(void)
{

	git_reference *reference, *master_ref, *resolved_ref;

	cl_git_pass(git_reference_lookup(&master_ref, g_repo, current_head_target));
	cl_git_pass(git_reference_lookup(&reference, g_repo, GIT_HEAD_FILE));

	cl_git_pass(git_reference_resolve(&resolved_ref, reference));
	cl_git_pass(git_oid_cmp(git_reference_oid(master_ref), git_reference_oid(resolved_ref)));

	git_reference_free(reference);
	git_reference_free(resolved_ref);
	git_reference_free(master_ref);
}
