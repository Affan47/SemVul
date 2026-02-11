initialize(const char *repo_name)
{
	_repo = cl_git_sandbox_init(repo_name);
	cl_git_pass(git_repository_index(&_index, _repo));

	_target = NULL;

	_pathspecs.strings = NULL;
	_pathspecs.count = 0;
}
