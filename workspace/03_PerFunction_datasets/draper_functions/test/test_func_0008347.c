connect_to_local_repository(const char *local_repository)
{
	build_local_file_url(&file_path_buf, local_repository);

	cl_git_pass(git_remote_new(&remote, repo, NULL, git_buf_cstr(&file_path_buf), NULL));
	cl_git_pass(git_remote_connect(remote, GIT_DIR_FETCH));

}
