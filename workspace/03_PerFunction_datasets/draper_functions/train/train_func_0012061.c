assert_hard_link(const char *path)
{

	struct stat st;

	cl_assert(git_path_isfile(path));
	cl_git_pass(p_stat(path, &st));
	cl_assert(st.st_nlink > 1);
}
