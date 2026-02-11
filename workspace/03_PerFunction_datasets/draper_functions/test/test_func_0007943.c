init_linked_repo(const char *path, const char *alternate)
{
	git_buf_clear(&destpath);
	git_buf_clear(&filepath);

	cl_git_pass(git_repository_init(&repo, path, 1));
	cl_git_pass(git_path_prettify(&destpath, alternate, NULL));
	cl_git_pass(git_buf_joinpath(&destpath, destpath.ptr, "objects"));
	cl_git_pass(git_buf_joinpath(&filepath, git_repository_path(repo), "objects/info"));
	cl_git_pass(git_futils_mkdir(filepath.ptr, NULL, 0755, GIT_MKDIR_PATH));
	cl_git_pass(git_buf_joinpath(&filepath, filepath.ptr , "alternates"));

	cl_git_pass(git_filebuf_open(&file, git_buf_cstr(&filepath), 0));
	git_filebuf_printf(&file, "%s\n", git_buf_cstr(&destpath));
	cl_git_pass(git_filebuf_commit(&file, 0644));

	git_repository_free(repo);
}
