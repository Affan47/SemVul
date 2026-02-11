cl_fake_home(void)
{
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_libgit2_opts(
		GIT_OPT_GET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, &path));

	_cl_restore_home = git_buf_detach(&path);
	cl_set_cleanup(cl_fake_home_cleanup, NULL);

	if (!git_path_exists("home"))
		cl_must_pass(p_mkdir("home", 0777));
	cl_git_pass(git_path_prettify(&path, "home", NULL));
	cl_git_pass(git_libgit2_opts(
		GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, path.ptr));
	git_buf_free(&path);
}
