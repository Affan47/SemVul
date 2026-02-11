test_revwalk_basic__push_all(void)
{
	git_oid oid;
	int i = 0;

	revwalk_basic_setup_walk(NULL);

	git_revwalk_reset(_walk);
	git_revwalk_sorting(_walk, 0);
	cl_git_pass(git_revwalk_push_glob(_walk, "*"));

	while (git_revwalk_next(&oid, _walk) == 0) {
		i++;
	}


	cl_assert_equal_i(15, i);
}
