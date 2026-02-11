test_odb_foreach__foreach(void)
{
	int nobj = 0;

	cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	git_repository_odb(&_odb, _repo);

	cl_git_pass(git_odb_foreach(_odb, foreach_cb, &nobj));
	cl_assert_equal_i(47 + 1640, nobj);
}
