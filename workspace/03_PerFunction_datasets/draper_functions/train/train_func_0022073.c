debugger_stop_real (Debugger *debugger)
{
	DEBUG_PRINT ("%s", "In function: debugger_stop_real()");


	if (debugger->priv->prog_is_attached == TRUE)
	{
		debugger_detach_process(debugger);
	}

	debugger->priv->terminating = TRUE;
	debugger_queue_command (debugger, "-gdb-exit", 0, NULL, NULL, NULL);
}
