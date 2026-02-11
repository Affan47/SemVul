wb_control_jump (WorkbookControl *wbc, Sheet *sheet, const GnmRangeRef *r)
{
	SheetView *sv;
	GnmCellPos tmp;

	if (r->a.sheet)
		sheet = r->a.sheet;

	if (!sheet_is_visible (sheet)) {
		go_cmd_context_error_invalid
			(GO_CMD_CONTEXT (wbc),
			 _("Cannot jump to an invisible sheet"),
			 sheet->name_unquoted);
		return FALSE;
	}

	sv = sheet_get_view (sheet, wb_control_view (wbc));

	tmp.col = r->a.col;
	tmp.row = r->a.row;
	sv_selection_set (sv, &tmp, r->a.col, r->a.row, r->b.col, r->b.row);
	sv_make_cell_visible (sv, r->b.col, r->b.row, FALSE);
	sv_make_cell_visible (sv, r->a.col, r->a.row, FALSE);
	sv_update (sv);
	if (wb_control_cur_sheet (wbc) != sheet)
		wb_view_sheet_focus (wbc->wb_view, sheet);

	return TRUE;
}
