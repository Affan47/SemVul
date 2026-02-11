test_network_remotelocal__initialize(void)
{
	cl_git_pass(git_repository_init(&repo, "remotelocal/", 0));
	cl_assert(repo != NULL);
}
