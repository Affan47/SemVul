test_online_clone__cred_callback_called_again_on_auth_failure(void)
{
	const char *remote_url = cl_getenv("GITTEST_REMOTE_URL");
	const char *remote_user = cl_getenv("GITTEST_REMOTE_USER");
	size_t counter = 0;

	if (!remote_url || !remote_user)
		clar__skip();

	g_options.remote_callbacks.credentials = cred_count_calls_cb;
	g_options.remote_callbacks.payload = &counter;

	cl_git_fail_with(GIT_EUSER, git_clone(&g_repo, remote_url, "./foo", &g_options));
	cl_assert_equal_i(3, counter);
}
