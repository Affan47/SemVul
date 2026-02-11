get_submodule_status(git_repository *repo, const char *name)
{
	git_submodule *sm = NULL;
	unsigned int status = 0;

	cl_git_pass(git_submodule_lookup(&sm, repo, name));
	cl_assert(sm);
	cl_git_pass(git_submodule_status(&status, sm));
	git_submodule_free(sm);

	return status;
}
