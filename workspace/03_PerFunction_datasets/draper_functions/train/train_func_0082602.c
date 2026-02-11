test_cleanup (void)
{
	CleanupParam param;

	param.value = DATA;

	egg_cleanup_register (cleanup_callback, &param);

	egg_cleanup_perform ();

	g_assert (param.value == NULL);
}
