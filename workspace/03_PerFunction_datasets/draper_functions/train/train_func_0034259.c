debugger_emit_ready (Debugger *debugger)
{
	if (!debugger->priv->debugger_is_busy)
	{
		if (debugger->priv->loading)
		{
			debugger->priv->starting = FALSE;
			debugger->priv->loading = FALSE;
			debugger->priv->exiting = FALSE;
			debugger->priv->stopping = FALSE;
			debugger->priv->solib_event = FALSE;
			g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_PROGRAM_LOADED);
		}
		else if (debugger->priv->starting)
		{
			debugger->priv->starting = FALSE;
			debugger->priv->loading = FALSE;
			debugger->priv->exiting = FALSE;
			debugger->priv->stopping = FALSE;
			debugger->priv->solib_event = FALSE;
			if (debugger->priv->prog_is_attached)
			{
				g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_PROGRAM_STOPPED);
			}
			else
			{
				g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_STARTED);
			}
		}
		else if (debugger->priv->exiting)
		{
			debugger->priv->exiting = FALSE;
			debugger->priv->stopping = FALSE;
			debugger->priv->solib_event = FALSE;
			g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_PROGRAM_LOADED);
		}
		else if (debugger->priv->solib_event)
		{
			debugger->priv->exiting = FALSE;
			debugger->priv->stopping = FALSE;
			debugger->priv->solib_event = FALSE;
			g_signal_emit_by_name (debugger->priv->instance, "sharedlib-event");
		}
		else if (debugger->priv->stopping)
		{
			debugger->priv->exiting = FALSE;
			debugger->priv->stopping = FALSE;
			debugger->priv->solib_event = FALSE;
			g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_PROGRAM_STOPPED);
		}
		else
		{
			if (debugger->priv->prog_is_running || debugger->priv->prog_is_attached)
			{
				g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_PROGRAM_STOPPED);
			}
			else if (debugger->priv->prog_is_loaded)
			{
				g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_PROGRAM_LOADED);
			}
			else
			{
				g_signal_emit_by_name (debugger->priv->instance, "debugger-ready", IANJUTA_DEBUGGER_STARTED);
			}
		}
	}
}
