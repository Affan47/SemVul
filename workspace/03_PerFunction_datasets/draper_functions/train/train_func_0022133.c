cmd_object_raise_undo (GnmCommand *cmd,
		       G_GNUC_UNUSED WorkbookControl *wbc)
{
	CmdObjectRaise *me = CMD_OBJECT_RAISE (cmd);
	if (me->changed_positions != 0)
		sheet_object_adjust_stacking (me->so, - me->changed_positions);
	return FALSE;
}
