debugger_run_to_position (Debugger *debugger, const gchar *file, guint line)
{
	gchar *buff;
	gchar *quoted_file;

	DEBUG_PRINT ("%s", "In function: debugger_run_to_position()");

	g_return_if_fail (IS_DEBUGGER (debugger));
	g_return_if_fail (debugger->priv->prog_is_running == TRUE);

	quoted_file = gdb_quote (file);
	buff = g_strdup_printf ("-break-insert -t %s \"\\\"%s\\\":%u\"",
							debugger->priv->has_pending_breakpoints ? "-f" : "",
							quoted_file, line);
	g_free (quoted_file);
	debugger_queue_command (debugger, buff, 0, NULL, NULL, NULL);
	g_free (buff);
	debugger_queue_command (debugger, "-exec-continue", 0, NULL, NULL, NULL);
}
