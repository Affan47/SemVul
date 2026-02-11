test_reset_soft__resetting_against_an_orphaned_head_repo_makes_the_head_no_longer_orphaned(void)
{
	git_reference *head;

	retrieve_target_from_oid(&target, repo, KNOWN_COMMIT_IN_BARE_REPO);

	make_head_orphaned(repo, NON_EXISTING_HEAD);

	cl_assert_equal_i(true, git_repository_head_orphan(repo));

	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT));

	cl_assert_equal_i(false, git_repository_head_orphan(repo));

	cl_git_pass(git_reference_lookup(&head, repo, NON_EXISTING_HEAD));
	cl_assert_equal_i(0, git_oid_streq(git_reference_target(head), KNOWN_COMMIT_IN_BARE_REPO));

	git_reference_free(head);
}
