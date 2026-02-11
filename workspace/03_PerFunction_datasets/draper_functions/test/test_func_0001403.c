test_refs_branches_create__default_reflog_message(void)
{
	git_reflog *log;
	const git_reflog_entry *entry;
	git_signature *sig;
	git_config *cfg;

	cl_git_pass(git_repository_config(&cfg, repo));
	cl_git_pass(git_config_set_string(cfg, "user.name", "Foo Bar"));
	cl_git_pass(git_config_set_string(cfg, "user.email", "foo@example.com"));
	git_config_free(cfg);

	cl_git_pass(git_signature_default(&sig, repo));

	retrieve_known_commit(&target, repo);
	cl_git_pass(git_branch_create(&branch, repo, NEW_BRANCH_NAME, target, false, NULL, NULL));
	cl_git_pass(git_reflog_read(&log, repo, "refs/heads/" NEW_BRANCH_NAME));

	entry = git_reflog_entry_byindex(log, 0);
	cl_assert_equal_s("Branch: created", git_reflog_entry_message(entry));
	cl_assert_equal_s(sig->email, git_reflog_entry_committer(entry)->email);

	git_reflog_free(log);
	git_signature_free(sig);
}
