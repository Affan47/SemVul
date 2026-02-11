test_stash_save__cannot_stash_against_an_unborn_branch(void)
{
	git_reference *head;

	cl_git_pass(git_reference_lookup(&head, repo, "HEAD"));
	cl_git_pass(git_reference_set_target(head, "refs/heads/unborn"));

	cl_assert_equal_i(GIT_EORPHANEDHEAD,
		git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_DEFAULT));

	git_reference_free(head);
}
