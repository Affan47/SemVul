test_refs_rename__writes_to_reflog(void)
{
	git_reference *ref, *new_ref;
	git_reflog *log;
	const git_reflog_entry *entry;
	git_signature *sig;

	cl_git_pass(git_signature_now(&sig, "me", "foo@example.com"));

	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_master_name));
	cl_git_pass(git_reference_rename(&new_ref, ref, ref_one_name_new, false,
				sig, "message"));
	cl_git_pass(git_reflog_read(&log, g_repo, git_reference_name(new_ref)));
	entry = git_reflog_entry_byindex(log, 0);
	cl_assert_equal_s("message", git_reflog_entry_message(entry));
	cl_assert_equal_s("foo@example.com", git_reflog_entry_committer(entry)->email);

	git_reflog_free(log);
	git_reference_free(ref);
	git_reference_free(new_ref);
	git_signature_free(sig);
}
