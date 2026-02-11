test_network_remote_local__shorthand_fetch_refspec0(void)
{
	const char *refspec = "master:remotes/sloppy/master";
	const char *refspec2 = "master:boh/sloppy/master";

	git_reference *ref;

	connect_to_local_repository(cl_fixture("testrepo.git"));
	cl_git_pass(git_remote_add_fetch(remote, refspec));
	cl_git_pass(git_remote_add_fetch(remote, refspec2));

	cl_git_pass(git_remote_download(remote, NULL, NULL));
	cl_git_pass(git_remote_update_tips(remote));

	cl_git_pass(git_reference_lookup(&ref, repo, "refs/remotes/sloppy/master"));
	git_reference_free(ref);

	cl_git_pass(git_reference_lookup(&ref, repo, "refs/heads/boh/sloppy/master"));
	git_reference_free(ref);
}
