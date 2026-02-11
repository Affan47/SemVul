test_checkout_index__calls_progress_callback(void)
{
	bool was_called = 0;
	g_opts.progress_cb = progress;
	g_opts.progress_payload = &was_called;

	cl_git_pass(git_checkout_index(g_repo, NULL, &g_opts));
	cl_assert_equal_i(was_called, true);
}
