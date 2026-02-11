set_git_dir_init(const char *git_dir, const char *real_git_dir,
		     int exist_ok)
{
	if (real_git_dir) {
		struct stat st;

		if (!exist_ok && !stat(git_dir, &st))
			die("%s already exists", git_dir);

		if (!exist_ok && !stat(real_git_dir, &st))
			die("%s already exists", real_git_dir);


		git_link = xstrdup(real_path(git_dir));
	}
	else {
		real_git_dir = real_path(git_dir);
		git_link = NULL;
	}
	set_git_dir(real_path(real_git_dir));
	return 0;
}
