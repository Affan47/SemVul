test_odb_backend_nonrefreshing__readheader_is_invoked_once_on_failure(void)
{
	git_odb *odb;
	size_t len;
	git_otype type;

	setup_repository_and_backend(GIT_ENOTFOUND);

	cl_git_pass(git_repository_odb__weakptr(&odb, _repo));

	cl_git_fail_with(
		git_odb_read_header(&len, &type, odb, &_oid),
		GIT_ENOTFOUND);

	cl_assert_equal_i(1, _fake->read_header_calls);
}
