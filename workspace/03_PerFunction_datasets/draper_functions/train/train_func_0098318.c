replace_daemon_at (const gchar *directory)
{
	gboolean ret;


	if (control_directory == NULL)
		control_directory = g_strdup (directory);

	ret = gkd_control_quit (directory, GKD_CONTROL_QUIET_IF_NO_PEER);


	if (ret == TRUE)
		g_usleep (200 * 1000);


	return FALSE;
}
