test_repo_head__set_head_Attaches_HEAD_to_un_unborn_branch_when_the_branch_doesnt_exist(void)
{
	git_reference *head;

	cl_git_pass(git_repository_set_head(repo, "refs/heads/doesnt/exist/yet", NULL, NULL));

	cl_assert_equal_i(false, git_repository_head_detached(repo));

	cl_assert_equal_i(GIT_EUNBORNBRANCH, git_repository_head(&head, repo));
}
