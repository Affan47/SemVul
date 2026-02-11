debugger_list_argument (Debugger *debugger, IAnjutaDebuggerGListCallback callback, gpointer user_data)
{
	gchar *buff;

	DEBUG_PRINT ("%s", "In function: debugger_list_argument()");

	g_return_if_fail (IS_DEBUGGER (debugger));

	buff = g_strdup_printf("-stack-list-arguments 0 %d %d", debugger->priv->current_frame, debugger->priv->current_frame);
	debugger_queue_command (debugger, buff, DEBUGGER_COMMAND_NO_ERROR, debugger_list_argument_finish, (IAnjutaDebuggerCallback)callback, user_data);
	g_free (buff);
}
