ensure_workdir_oid(const char *path, const char *oid_str)
{
	git_oid expected, actual;

	cl_git_pass(git_oid_fromstr(&expected, oid_str));
	cl_git_pass(git_repository_hashfile(&actual, g_repo, path, GIT_OBJ_BLOB, NULL));
	cl_assert_equal_oid(&expected, &actual);
}
