assert_retrieval(unsigned int flags, unsigned int expected_count)
{
	int count = 0;

	cl_git_pass(git_branch_foreach(repo, flags, count_branch_list_cb, &count));

	cl_assert_equal_i(expected_count, count);
}
