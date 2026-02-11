init_shell (TerminalPlugin *term_plugin, const char *path)
{
	gchar *shell[2] = {0, 0};
	static gboolean first_time = TRUE;
	VteTerminal *term = VTE_TERMINAL (term_plugin->shell);

	shell[0] = vte_get_user_shell ();
	if (shell[0] == NULL) shell[0] = g_strdup("/bin/sh");

	if (!first_time)
		vte_terminal_reset (term, FALSE, TRUE);
	else
		first_time = FALSE;

	vte_terminal_fork_command_full (term, term_plugin->pty_flags,
	                                path, shell, NULL,
	                                0, NULL, NULL,
	                                NULL, NULL);
	g_free (shell[0]);
}
