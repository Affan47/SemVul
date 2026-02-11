test_repo_open__bad_gitlinks(void)
{
	git_repository *repo;
	static const char *bad_links[] = {
		"garbage\n", "gitdir", "gitdir:\n", "gitdir: foobar",
		"gitdir: ../invalid", "gitdir: ../invalid2",
		"gitdir: ../attr/.git with extra stuff",
		NULL
	};
	const char **scan;

	cl_git_sandbox_init("attr");

	cl_git_pass(p_mkdir("invalid", 0777));
	cl_git_pass(git_futils_mkdir_r("invalid2/.git", NULL, 0777));

	for (scan = bad_links; *scan != NULL; scan++) {
		make_gitlink_dir("alternate", *scan);
		cl_git_fail(git_repository_open_ext(&repo, "alternate", 0, NULL));
	}

	git_futils_rmdir_r("invalid", NULL, GIT_RMDIR_REMOVE_FILES);
	git_futils_rmdir_r("invalid2", NULL, GIT_RMDIR_REMOVE_FILES);
}
