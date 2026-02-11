cmd_resize_sheets_finalize (GObject *cmd)
{
	CmdResizeSheets *me = CMD_RESIZE_SHEETS (cmd);

	g_slist_free (me->sheets);
	if (me->undo) {
		g_object_unref (me->undo);
		me->undo = NULL;
	}

	gnm_command_finalize (cmd);
}
