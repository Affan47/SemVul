test_refs_reflog_drop__can_drop_all_the_entries(void)
{
	cl_assert(--entrycount > 0);

	do 	{
		cl_git_pass(git_reflog_drop(g_reflog, 0, 1));
	} while (--entrycount > 0);

	cl_git_pass(git_reflog_drop(g_reflog, 0, 1));

	cl_assert_equal_i(0, (int)git_reflog_entrycount(g_reflog));
}
