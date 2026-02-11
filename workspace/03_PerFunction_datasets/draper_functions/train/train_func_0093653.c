scg_select_all (SheetControlGUI *scg)
{
	Sheet *sheet = scg_sheet (scg);
	gboolean const rangesel = wbcg_rangesel_possible (scg->wbcg);

	if (rangesel) {
		scg_rangesel_bound (scg,
			0, 0, gnm_sheet_get_last_col (sheet), gnm_sheet_get_last_row (sheet));
		gnm_expr_entry_signal_update (
			wbcg_get_entry_logical (scg->wbcg), TRUE);
	} else if (wbc_gtk_get_guru (scg->wbcg) == NULL) {
		SheetView *sv = scg_view (scg);

		scg_mode_edit (scg);
		wbcg_edit_finish (scg->wbcg, WBC_EDIT_REJECT, NULL);
		sv_selection_reset (sv);
		sv_selection_add_full (sv, sv->edit_pos.col, sv->edit_pos.row,
				       0, 0, gnm_sheet_get_last_col (sheet),
				       gnm_sheet_get_last_row (sheet),
				       GNM_SELECTION_MODE_ADD);
	}
	sheet_update (sheet);
}
