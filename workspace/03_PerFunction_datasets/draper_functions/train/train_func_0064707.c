test_refs_branches_delete__can_not_delete_a_branch_if_HEAD_is_missing(void)
{
	git_reference *head;

	cl_git_pass(git_reference_lookup(&head, repo, GIT_HEAD_FILE));
	git_reference_delete(head);

	cl_git_fail(git_branch_delete(repo, "br2", GIT_BRANCH_LOCAL));
}
