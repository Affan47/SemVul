on_terminal_command_cb (GtkAction * action, TerminalPlugin *term_plugin)
{
	VteTerminal *term;
	gchar c;

	if (term_plugin->child_pid)
		term = VTE_TERMINAL (term_plugin->term);
	else
		term = VTE_TERMINAL (term_plugin->shell);


	c = gtk_action_get_name (action) [strlen (gtk_action_get_name (action)) - 1] - 64;

	vte_terminal_feed_child (term, &c, 1);
}
