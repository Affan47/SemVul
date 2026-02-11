test_network_remote_remotes__error_when_no_push_available(void)
{
	git_remote *r;
	git_push *p;

	cl_git_pass(git_remote_create_anonymous(&r, _repo, cl_fixture("testrepo.git"), NULL));

	cl_git_pass(git_remote_set_transport(r, git_transport_local, NULL));

	cl_git_pass(git_remote_connect(r, GIT_DIRECTION_PUSH));


	r->transport->push = NULL;

	cl_git_pass(git_push_new(&p, r));
	cl_git_pass(git_push_add_refspec(p, "refs/heads/master"));
	cl_git_fail_with(git_push_finish(p), GIT_ERROR);

	git_push_free(p);
	git_remote_free(r);
}
