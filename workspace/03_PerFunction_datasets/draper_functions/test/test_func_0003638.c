up_backend_supports_sleep_state (const gchar *state)
{
	gboolean ret = FALSE;
	gchar *command;
	GError *error = NULL;
	gint exit_status;


	command = g_strdup_printf ("/usr/bin/pm-is-supported --%s", state);
	g_debug ("excuting command: %s", command);
	ret = g_spawn_command_line_sync (command, NULL, NULL, &exit_status, &error);
	if (!ret) {
		g_warning ("failed to run script: %s", error->message);
		g_error_free (error);
		goto out;
	}
	ret = (WIFEXITED(exit_status) && (WEXITSTATUS(exit_status) == EXIT_SUCCESS));

out:
	g_free (command);
	return ret;
}
