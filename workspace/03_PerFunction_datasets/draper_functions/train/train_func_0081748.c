test_checkout_index__can_overcome_name_clashes(void)
{
	git_index *index;

	cl_git_pass(git_repository_index(&index, g_repo));
	git_index_clear(index);

	cl_git_mkfile("./testrepo/path0", "content\r\n");
	cl_git_pass(p_mkdir("./testrepo/path1", 0777));
	cl_git_mkfile("./testrepo/path1/file1", "content\r\n");

	cl_git_pass(git_index_add_from_workdir(index, "path0"));
	cl_git_pass(git_index_add_from_workdir(index, "path1/file1"));


	cl_git_pass(p_unlink("./testrepo/path0"));
	cl_git_pass(git_futils_rmdir_r(
		"./testrepo/path1", NULL, GIT_RMDIR_REMOVE_FILES));

	cl_git_mkfile("./testrepo/path1", "content\r\n");
	cl_git_pass(p_mkdir("./testrepo/path0", 0777));
	cl_git_mkfile("./testrepo/path0/file0", "content\r\n");

	cl_assert(git_path_isfile("./testrepo/path1"));
	cl_assert(git_path_isfile("./testrepo/path0/file0"));

	g_opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_ALLOW_CONFLICTS;
	cl_git_pass(git_checkout_index(g_repo, NULL, &g_opts));

	cl_assert(git_path_isfile("./testrepo/path1"));
	cl_assert(git_path_isfile("./testrepo/path0/file0"));

	g_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_index(g_repo, NULL, &g_opts));

	cl_assert(git_path_isfile("./testrepo/path0"));
	cl_assert(git_path_isfile("./testrepo/path1/file1"));

	git_index_free(index);
}
