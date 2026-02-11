dma_command_cancel (DmaQueueCommand *cmd)
{
	GError *err = g_error_new_literal (IANJUTA_DEBUGGER_ERROR , IANJUTA_DEBUGGER_CANCEL, "Command cancel");

	if (cmd->callback != NULL)
	{
		cmd->callback (NULL, cmd->user_data, err);
	}

	g_error_free (err);

	g_warning ("Cancel command %x\n", cmd->type);

	dma_command_free (cmd);
}
