test_refs_branches_delete__can_delete_a_branch_even_if_HEAD_is_missing(void)
{
	git_reference *head;
	git_reference *branch;

	cl_git_pass(git_reference_lookup(&head, repo, GIT_HEAD_FILE));
	git_reference_delete(head);
	git_reference_free(head);

	cl_git_pass(git_branch_lookup(&branch, repo, "br2", GIT_BRANCH_LOCAL));
	cl_git_pass(git_branch_delete(branch));
	git_reference_free(branch);
}
