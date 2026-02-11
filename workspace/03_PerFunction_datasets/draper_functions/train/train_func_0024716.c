test_async_none (void)
{
	GError *error = NULL;
	EchoData data;
	guint ret;

	memset (&data, 0, sizeof (data));
	data.parent_pid = getpid();
	data.is_async = TRUE;

	ret = egg_spawn_async_with_callbacks (SRCDIR "/files",
	                                     echo_argv, NULL, 0, NULL,
	                                     &null_callbacks, &data,
	                                     NULL, &error);
	g_assert (ret != 0);
	g_assert (error == NULL);
	g_assert (!data.finalized);

	egg_test_wait_until (2000);

	g_assert (data.finalized);
	g_assert (data.completed);
	g_assert (!data.output);
}
