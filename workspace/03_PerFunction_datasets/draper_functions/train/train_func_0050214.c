test_revwalk_basic__glob_heads(void)
{
	int i = 0;
	git_oid oid;

	revwalk_basic_setup_walk(NULL);

	cl_git_pass(git_revwalk_push_glob(_walk, "heads"));

	while (git_revwalk_next(&oid, _walk) == 0) {
		i++;
	}


	cl_assert_equal_i(i, 14);
}
