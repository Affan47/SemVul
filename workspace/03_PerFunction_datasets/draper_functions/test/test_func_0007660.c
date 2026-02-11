test_network_fetchlocal__multi_remotes(void)
{
	git_repository *repo = cl_git_sandbox_init("testrepo.git");
	git_remote *test, *test2;
	git_strarray refnames = {0};
	git_remote_callbacks callbacks = GIT_REMOTE_CALLBACKS_INIT;

	cl_set_cleanup(&cleanup_sandbox, NULL);
	callbacks.transfer_progress = transfer_cb;
	cl_git_pass(git_remote_load(&test, repo, "test"));
	cl_git_pass(git_remote_set_url(test, cl_git_fixture_url("testrepo.git")));
	git_remote_set_callbacks(test, &callbacks);
	cl_git_pass(git_remote_connect(test, GIT_DIRECTION_FETCH));
	cl_git_pass(git_remote_download(test, NULL));
	cl_git_pass(git_remote_update_tips(test, NULL, NULL));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(32, (int)refnames.count);
	git_strarray_free(&refnames);

	cl_git_pass(git_remote_load(&test2, repo, "test_with_pushurl"));
	cl_git_pass(git_remote_set_url(test2, cl_git_fixture_url("testrepo.git")));
	git_remote_set_callbacks(test2, &callbacks);
	cl_git_pass(git_remote_connect(test2, GIT_DIRECTION_FETCH));
	cl_git_pass(git_remote_download(test2, NULL));
	cl_git_pass(git_remote_update_tips(test2, NULL, NULL));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(44, (int)refnames.count);

	git_strarray_free(&refnames);
	git_remote_free(test);
	git_remote_free(test2);
}
