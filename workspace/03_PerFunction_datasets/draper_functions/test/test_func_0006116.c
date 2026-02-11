test_network_remote_local__fetch(void)
{
	char *refspec_strings[] = {
		"master:remotes/sloppy/master",
	};
	git_strarray array = {
		refspec_strings,
		1,
	};

	git_reflog *log;
	const git_reflog_entry *entry;
	git_signature *sig;
	git_reference *ref;

	cl_git_pass(git_signature_now(&sig, "Foo Bar", "foo@example.com"));

	connect_to_local_repository(cl_fixture("testrepo.git"));

	cl_git_pass(git_remote_fetch(remote, &array, sig, "UPDAAAAAATE!!"));

	cl_git_pass(git_reference_lookup(&ref, repo, "refs/remotes/sloppy/master"));
	git_reference_free(ref);

	cl_git_pass(git_reflog_read(&log, repo, "refs/remotes/sloppy/master"));
	cl_assert_equal_i(1, git_reflog_entrycount(log));
	entry = git_reflog_entry_byindex(log, 0);
	cl_assert_equal_s("foo@example.com", git_reflog_entry_committer(entry)->email);
	cl_assert_equal_s("UPDAAAAAATE!!", git_reflog_entry_message(entry));

	git_reflog_free(log);
	git_signature_free(sig);
}
