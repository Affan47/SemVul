test_online_fetch__doesnt_retrieve_a_pack_when_the_repository_is_up_to_date(void)
{
	git_repository *_repository;
	bool invoked = false;
	git_remote *remote;
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	opts.bare = true;

	cl_git_pass(git_clone(&_repository, "https://github.com/libgit2/TestGitRepository.git",
				"./fetch/lg2", &opts));
	git_repository_free(_repository);

	cl_git_pass(git_repository_open(&_repository, "./fetch/lg2"));

	cl_git_pass(git_remote_load(&remote, _repository, "origin"));
	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH));

	cl_assert_equal_i(false, invoked);

	cl_git_pass(git_remote_download(remote, &transferProgressCallback, &invoked));

	cl_assert_equal_i(false, invoked);

	cl_git_pass(git_remote_update_tips(remote));
	git_remote_disconnect(remote);

	git_remote_free(remote);
	git_repository_free(_repository);
}
