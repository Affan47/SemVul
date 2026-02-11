test_refs_branches_move__can_move_with_unicode(void)
{
	git_reference *original_ref, *new_ref;
	const char *new_branch_name = "\x41\xCC\x8A\x73\x74\x72\x6F\xCC\x88\x6D";

	cl_git_pass(git_reference_lookup(&original_ref, repo, "refs/heads/br2"));
	cl_git_pass(git_branch_move(&new_ref, original_ref, new_branch_name, 0, NULL, NULL));

	if (cl_repo_get_bool(repo, "core.precomposeunicode"))
		cl_assert_equal_s(GIT_REFS_HEADS_DIR "\xC3\x85\x73\x74\x72\xC3\xB6\x6D", git_reference_name(new_ref));
	else
		cl_assert_equal_s(GIT_REFS_HEADS_DIR "\x41\xCC\x8A\x73\x74\x72\x6F\xCC\x88\x6D", git_reference_name(new_ref));

	git_reference_free(original_ref);
	git_reference_free(new_ref);
}
