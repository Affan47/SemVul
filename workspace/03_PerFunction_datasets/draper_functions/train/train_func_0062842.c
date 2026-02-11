test_refs_branches_foreach__retrieve_remote_symbolic_HEAD_when_present(void)
{
	struct expectations exp[] = {
		{ "nulltoken/HEAD", 0 },
		{ "nulltoken/master", 0 },
		{ NULL, 0 }
	};

	git_reference_free(fake_remote);
	cl_git_pass(git_reference_symbolic_create(&fake_remote, repo, "refs/remotes/nulltoken/HEAD", "refs/remotes/nulltoken/master", 0));

	assert_retrieval(GIT_BRANCH_REMOTE, 3);

	cl_git_pass(git_branch_foreach(repo, GIT_BRANCH_REMOTE, contains_branch_list_cb, &exp));

	assert_branch_has_been_found(exp, "nulltoken/HEAD");
	assert_branch_has_been_found(exp, "nulltoken/HEAD");
}
