test_stash_save__cannot_stash_against_a_bare_repository(void)
{
	git_repository *local;

	cl_git_pass(git_repository_init(&local, "sorry-it-is-a-non-bare-only-party", 1));

	cl_assert_equal_i(GIT_EBAREREPO,
		git_stash_save(&stash_tip_oid, local, signature, NULL, GIT_STASH_DEFAULT));

	git_repository_free(local);
}
