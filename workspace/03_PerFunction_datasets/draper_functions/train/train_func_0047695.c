test_stash_foreach__can_enumerate_a_repository(void)
{
	char *oids_default[] = {
		"1d91c842a7cdfc25872b3a763e5c31add8816c25", NULL };

	char *oids_untracked[] = {
		"7f89a8b15c878809c5c54d1ff8f8c9674154017b",
		"1d91c842a7cdfc25872b3a763e5c31add8816c25", NULL };

	char *oids_ignored[] = {
		"c95599a8fef20a7e57582c6727b1a0d02e0a5828",
		"7f89a8b15c878809c5c54d1ff8f8c9674154017b",
		"1d91c842a7cdfc25872b3a763e5c31add8816c25", NULL };

	cl_git_pass(git_repository_init(&repo, REPO_NAME, 0));

	setup_stash(repo, signature);

	cl_git_pass(git_stash_save(
		&stash_tip_oid,
		repo,
		signature,
		NULL,
		GIT_STASH_DEFAULT));

	data.oids = oids_default;

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));
	cl_assert_equal_i(1, data.invokes);

	data.oids = oids_untracked;
	data.invokes = 0;

	cl_git_pass(git_stash_save(
		&stash_tip_oid,
		repo,
		signature,
		NULL,
		GIT_STASH_INCLUDE_UNTRACKED));

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));
	cl_assert_equal_i(2, data.invokes);

	data.oids = oids_ignored;
	data.invokes = 0;

	cl_git_pass(git_stash_save(
		&stash_tip_oid,
		repo,
		signature,
		NULL,
		GIT_STASH_INCLUDE_IGNORED));

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));
	cl_assert_equal_i(3, data.invokes);
}
