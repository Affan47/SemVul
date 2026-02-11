test_refs_reflog__write_then_read(void)
{

   git_repository *repo2;
	git_reference *ref, *lookedup_ref;
	git_oid oid;
	git_signature *committer;
	git_reflog *reflog;
	git_reflog_entry *entry;
	char oid_str[GIT_OID_HEXSZ+1];


	git_oid_fromstr(&oid, current_master_tip);
	cl_git_pass(git_reference_create_oid(&ref, g_repo, new_ref, &oid, 0));
	git_reference_free(ref);
	cl_git_pass(git_reference_lookup(&ref, g_repo, new_ref));

	cl_git_pass(git_signature_now(&committer, "foo", "foo@bar"));

	cl_git_pass(git_reflog_write(ref, NULL, committer, NULL));
	cl_git_fail(git_reflog_write(ref, NULL, committer, "no ancestor NULL for an existing reflog"));
	cl_git_fail(git_reflog_write(ref, NULL, committer, "no\nnewline"));
	cl_git_pass(git_reflog_write(ref, &oid, committer, commit_msg));


	cl_git_pass(git_repository_open(&repo2, "testrepo"));


	cl_git_pass(git_reference_lookup(&lookedup_ref, repo2, new_ref));


	cl_git_pass(git_reflog_read(&reflog, lookedup_ref));
	cl_assert(reflog->entries.length == 2);

	entry = (git_reflog_entry *)git_vector_get(&reflog->entries, 0);
	assert_signature(committer, entry->committer);
	git_oid_tostr(oid_str, GIT_OID_HEXSZ+1, &entry->oid_old);
	cl_assert_equal_s("0000000000000000000000000000000000000000", oid_str);
	git_oid_tostr(oid_str, GIT_OID_HEXSZ+1, &entry->oid_cur);
	cl_assert_equal_s(current_master_tip, oid_str);
	cl_assert(entry->msg == NULL);

	entry = (git_reflog_entry *)git_vector_get(&reflog->entries, 1);
	assert_signature(committer, entry->committer);
	git_oid_tostr(oid_str, GIT_OID_HEXSZ+1, &entry->oid_old);
	cl_assert_equal_s(current_master_tip, oid_str);
	git_oid_tostr(oid_str, GIT_OID_HEXSZ+1, &entry->oid_cur);
	cl_assert_equal_s(current_master_tip, oid_str);
	cl_assert_equal_s(commit_msg, entry->msg);

	git_signature_free(committer);
	git_reflog_free(reflog);
	git_repository_free(repo2);

	git_reference_free(ref);
	git_reference_free(lookedup_ref);
}
