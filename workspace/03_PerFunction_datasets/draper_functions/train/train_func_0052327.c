execute_async(gchar *const argv[])
{
	cm_return_val_if_fail(argv != NULL && argv[0] != NULL, -1);

	if (g_spawn_async(NULL, (gchar **)argv, NULL, G_SPAWN_SEARCH_PATH,
			  NULL, NULL, NULL, FALSE) == FALSE) {
		g_warning("Couldn't execute command: %s\n", argv[0]);
		return -1;
	}

	return 0;
}
