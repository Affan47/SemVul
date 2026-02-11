test_stash_save__can_keep_index(void)
{
	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_KEEP_INDEX));

	assert_status(repo, "what", GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "how", GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "who", GIT_STATUS_CURRENT);
	assert_status(repo, "when", GIT_STATUS_WT_NEW);
	assert_status(repo, "just.ignore", GIT_STATUS_IGNORED);
}
