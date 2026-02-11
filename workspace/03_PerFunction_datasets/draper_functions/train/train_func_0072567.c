test_reset_default__resetting_unknown_filepaths_does_not_fail(void)
{
	char *paths[] = { "I_am_not_there.txt", "me_neither.txt" };

	initialize("status");

	_pathspecs.strings = paths;
	_pathspecs.count = 2;

	assert_content_in_index(&_pathspecs, false, NULL);

	cl_git_pass(git_revparse_single(&_target, _repo, "HEAD"));
	cl_git_pass(git_reset_default(_repo, _target, &_pathspecs));

	assert_content_in_index(&_pathspecs, false, NULL);
}
