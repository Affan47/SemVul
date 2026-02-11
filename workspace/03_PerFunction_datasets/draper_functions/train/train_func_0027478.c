debugger_write_register (Debugger *debugger, const gchar *name, const gchar *value)
{
	gchar *buf;

	DEBUG_PRINT ("%s", "In function: debugger_write_register()");

	g_return_if_fail (IS_DEBUGGER (debugger));

	buf = g_strdup_printf ("-data-evaluate-expression \"$%s=%s\"", name, value);
	debugger_queue_command (debugger, buf, DEBUGGER_COMMAND_NO_ERROR, NULL, NULL, NULL);
	g_free (buf);
}
