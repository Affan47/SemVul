test_refs_branches_move__moving_the_branch_pointed_at_by_HEAD_updates_HEAD(void)
{
	git_reference *branch;
	git_reference *new_branch;

	cl_git_pass(git_reference_lookup(&branch, repo, "refs/heads/master"));
	cl_git_pass(git_branch_move(&new_branch, branch, "master2", 0));
	git_reference_free(branch);
	git_reference_free(new_branch);

	cl_git_pass(git_repository_head(&branch, repo));
	cl_assert_equal_s("refs/heads/master2", git_reference_name(branch));
	git_reference_free(branch);
}
