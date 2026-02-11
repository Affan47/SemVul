cmd_reorganize_sheets_redo (GnmCommand *cmd, WorkbookControl *wbc)
{
	CmdReorganizeSheets *me = CMD_REORGANIZE_SHEETS (cmd);

	if (me->first)
		me->first = FALSE;
	else {
		workbook_sheet_state_restore (me->wb, me->new);
		if (me->redo_sheet) {
			WORKBOOK_VIEW_FOREACH_CONTROL (wb_control_view (wbc), control,
						       wb_control_sheet_focus (control, me->redo_sheet););
		}
	}

	return FALSE;
}
