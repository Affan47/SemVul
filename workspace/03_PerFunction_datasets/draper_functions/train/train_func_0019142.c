cmd_resize_sheets (WorkbookControl *wbc,
		   GSList *sheets,
		   int cols, int rows)
{
	CmdResizeSheets *me;

	me = g_object_new (CMD_RESIZE_SHEETS_TYPE, NULL);
	me->sheets = sheets;
	me->cols = cols;
	me->rows = rows;
	me->cmd.sheet = sheets ? sheets->data : NULL;
	me->cmd.size = 1;
	me->cmd.cmd_descriptor = g_strdup (_("Resizing sheet"));

	if (sheets &&
	    gnm_sheet_valid_size (cols, rows))
		return gnm_command_push_undo (wbc, G_OBJECT (me));


	g_object_unref (me);
	return FALSE;
}
