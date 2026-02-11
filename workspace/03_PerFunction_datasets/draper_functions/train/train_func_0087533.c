cb_accept_input_selected_merged (WBCGtk *wbcg)
{
	Sheet *sheet = wbcg->editing_sheet;

#warning FIXME: this creates 2 undo items!
	if (wbcg_is_editing (wbcg) &&
	    wbcg_edit_finish (wbcg, WBC_EDIT_ACCEPT, NULL)) {
		WorkbookControl *wbc = WORKBOOK_CONTROL (wbcg);
		WorkbookView	*wbv = wb_control_view (wbc);
		SheetView *sv = sheet_get_view (sheet, wbv);
		GnmRange sel = *(selection_first_range (sv, NULL, NULL));
		GSList *selection = g_slist_prepend (NULL, &sel);

		cmd_merge_cells	(wbc, sheet, selection, FALSE);
		g_slist_free (selection);
	}
}
