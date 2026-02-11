test_merge_workdir_setup__normal_branch_and_remote_tracking_branch(void)
{
	git_oid our_oid;
	git_reference *octo1_ref;
	git_reference *octo2_ref;
	git_merge_head *our_head, *their_heads[2];

	cl_git_pass(create_remote_tracking_branch(OCTO2_BRANCH, OCTO2_OID));

	cl_git_pass(git_oid_fromstr(&our_oid, ORIG_HEAD));
	cl_git_pass(git_merge_head_from_oid(&our_head, repo, &our_oid));

	cl_git_pass(git_reference_lookup(&octo1_ref, repo, GIT_REFS_HEADS_DIR OCTO1_BRANCH));
	cl_git_pass(git_merge_head_from_ref(&their_heads[0], repo, octo1_ref));

	cl_git_pass(git_reference_lookup(&octo2_ref, repo, GIT_REFS_REMOTES_DIR "origin/" OCTO2_BRANCH));
	cl_git_pass(git_merge_head_from_ref(&their_heads[1], repo, octo2_ref));

	cl_git_pass(git_merge__setup(repo, our_head, (const git_merge_head **)their_heads, 2, 0));

	cl_assert(test_file_contents(GIT_MERGE_HEAD_FILE, OCTO1_OID "\n" OCTO2_OID "\n"));
	cl_assert(test_file_contents(GIT_ORIG_HEAD_FILE, ORIG_HEAD "\n"));
	cl_assert(test_file_contents(GIT_MERGE_MODE_FILE, ""));
	cl_assert(test_file_contents(GIT_MERGE_MSG_FILE, "Merge branch '" OCTO1_BRANCH "', remote-tracking branch 'refs/remotes/origin/" OCTO2_BRANCH "'\n"));

	git_reference_free(octo1_ref);
	git_reference_free(octo2_ref);

	git_merge_head_free(our_head);
	git_merge_head_free(their_heads[0]);
	git_merge_head_free(their_heads[1]);
}
