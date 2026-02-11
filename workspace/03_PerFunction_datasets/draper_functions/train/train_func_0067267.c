test_network_remote_defaultbranch__detached_sharing_nonbranch_id(void)
{
	git_oid id, id_cloned;
	git_reference *ref;
	git_buf buf = GIT_BUF_INIT;
	git_repository *cloned_repo;

	cl_git_pass(git_reference_name_to_id(&id, g_repo_a, "HEAD"));
	cl_git_pass(git_repository_detach_head(g_repo_a, NULL, NULL));
	cl_git_pass(git_reference_remove(g_repo_a, "refs/heads/master"));
	cl_git_pass(git_reference_remove(g_repo_a, "refs/heads/not-good"));
	cl_git_pass(git_reference_create(&ref, g_repo_a, "refs/foo/bar", &id, 1, NULL, NULL));
	git_reference_free(ref);

	cl_git_pass(git_remote_connect(g_remote, GIT_DIRECTION_FETCH));
	cl_git_fail_with(GIT_ENOTFOUND, git_remote_default_branch(&buf, g_remote));

	cl_git_pass(git_clone(&cloned_repo, git_repository_path(g_repo_a), "./local-detached", NULL));

	cl_assert(git_repository_head_detached(cloned_repo));
	cl_git_pass(git_reference_name_to_id(&id_cloned, g_repo_a, "HEAD"));
	cl_assert(git_oid_equal(&id, &id_cloned));

	git_repository_free(cloned_repo);
}
