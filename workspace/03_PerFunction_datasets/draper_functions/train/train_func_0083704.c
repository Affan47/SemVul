debugger_set_environment (Debugger *debugger, gchar **variables)
{
	gchar *buff;

	DEBUG_PRINT ("%s", "In function: set_environment()");

	g_return_val_if_fail (IS_DEBUGGER (debugger), FALSE);

	if ((variables != NULL)  && (*variables != NULL))
	{
		for (; *variables != NULL; variables++)
		{
			buff = g_strdup_printf("set environment %s", *variables);
			debugger_queue_command (debugger, buff, 0, NULL, NULL, NULL);
			g_free (buff);
		}
	}
	else
	{
		debugger_emit_ready (debugger);
	}

	return TRUE;
}
