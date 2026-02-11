netinfo_reap_child (GPid pid, gint status, gpointer user_data)
{
	Netinfo *netinfo = (Netinfo *) user_data;
	gchar *primary = NULL;
	gchar *secondary = NULL;
	const gchar *page_label;
	gchar *cmd;

	g_spawn_close_pid (pid);

	g_return_if_fail (netinfo != NULL);
	g_return_if_fail (netinfo->command_line != NULL);

	page_label = gtk_label_get_text (GTK_LABEL (netinfo->page_label));

	if (WEXITSTATUS(status) > 0) {
		cmd = g_strjoinv (" ", netinfo->command_line);


		primary = g_strdup_printf (
				_("An error occurred when try to run '%s'"),
				page_label);
		secondary = g_strdup_printf ("%s", cmd);

		netinfo_error_message (netinfo, primary, secondary);

		g_free (cmd);
		g_free (primary);
		g_free (secondary);
	}
}
