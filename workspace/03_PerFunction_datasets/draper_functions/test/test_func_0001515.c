test_refs_reflog_reflog__append_then_read(void)
{

	git_repository *repo2;
	git_reference *ref, *lookedup_ref;
	git_oid oid;
	git_signature *committer;
	git_reflog *reflog;
	const git_reflog_entry *entry;


	git_oid_fromstr(&oid, current_master_tip);
	cl_git_pass(git_reference_create_oid(&ref, g_repo, new_ref, &oid, 0));

	cl_git_pass(git_signature_now(&committer, "foo", "foo@bar"));

	cl_git_pass(git_reflog_read(&reflog, ref));

	cl_git_fail(git_reflog_append(reflog, &oid, committer, "no inner\nnewline"));
	cl_git_pass(git_reflog_append(reflog, &oid, committer, NULL));
	cl_git_pass(git_reflog_append(reflog, &oid, committer, commit_msg "\n"));
	cl_git_pass(git_reflog_write(reflog));
	git_reflog_free(reflog);


	cl_git_pass(git_repository_open(&repo2, "testrepo.git"));


	cl_git_pass(git_reference_lookup(&lookedup_ref, repo2, new_ref));


	cl_git_pass(git_reflog_read(&reflog, lookedup_ref));
	cl_assert_equal_i(2, git_reflog_entrycount(reflog));

	entry = git_reflog_entry_byindex(reflog, 0);
	assert_signature(committer, entry->committer);
	cl_assert(git_oid_streq(&entry->oid_old, GIT_OID_HEX_ZERO) == 0);
	cl_assert(git_oid_cmp(&oid, &entry->oid_cur) == 0);
	cl_assert(entry->msg == NULL);

	entry = git_reflog_entry_byindex(reflog, 1);
	assert_signature(committer, entry->committer);
	cl_assert(git_oid_cmp(&oid, &entry->oid_old) == 0);
	cl_assert(git_oid_cmp(&oid, &entry->oid_cur) == 0);
	cl_assert_equal_s(commit_msg, entry->msg);

	git_signature_free(committer);
	git_reflog_free(reflog);
	git_repository_free(repo2);

	git_reference_free(ref);
	git_reference_free(lookedup_ref);
}
