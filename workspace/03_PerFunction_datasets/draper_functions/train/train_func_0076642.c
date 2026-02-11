tracker_spawn_async_with_channels (const gchar **argv,
                                   gint          timeout,
                                   GPid         *pid,
                                   GIOChannel  **stdin_channel,
                                   GIOChannel  **stdout_channel,
                                   GIOChannel  **stderr_channel)
{
	GError   *error = NULL;
	gboolean  result;
	gint      tmpstdin, tmpstdout, tmpstderr;

	g_return_val_if_fail (argv != NULL, FALSE);
	g_return_val_if_fail (argv[0] != NULL, FALSE);
	g_return_val_if_fail (timeout >= 0, FALSE);
	g_return_val_if_fail (pid != NULL, FALSE);


	result = g_spawn_async_with_pipes (NULL,
	                                   (gchar **) argv,
	                                   NULL,
	                                   G_SPAWN_SEARCH_PATH | G_SPAWN_DO_NOT_REAP_CHILD,
	                                   tracker_spawn_child_func,
	                                   GINT_TO_POINTER (timeout),
	                                   pid,
	                                   stdin_channel ? &tmpstdin : NULL,
	                                   stdout_channel ? &tmpstdout : NULL,
	                                   stderr_channel ? &tmpstderr : NULL,
	                                   &error);

	if (error) {
		g_warning ("Could not spawn command:'%s', %s",
		           argv[0],
		           error->message);
		g_error_free (error);
	}

	if (stdin_channel) {
		*stdin_channel = result ? g_io_channel_unix_new (tmpstdin) : NULL;
	}

	if (stdout_channel) {
		*stdout_channel = result ? g_io_channel_unix_new (tmpstdout) : NULL;
	}

	if (stderr_channel) {
		*stderr_channel = result ? g_io_channel_unix_new (tmpstderr) : NULL;
	}

	return result;
}
