test_core_rmdir__fail_to_delete_non_empty_dir(void)
{
	git_buf file = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&file, empty_tmp_dir, "/two/file.txt"));

	cl_git_mkfile(git_buf_cstr(&file), "dummy");

	cl_git_fail(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_EMPTY_HIERARCHY));

	cl_must_pass(p_unlink(file.ptr));
	cl_git_pass(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_EMPTY_HIERARCHY));

	git_buf_free(&file);
}
