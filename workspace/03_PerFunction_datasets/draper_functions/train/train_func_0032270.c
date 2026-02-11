gnm_pane_set_top_row (GnmPane *pane, int new_first_row)
{
	Sheet *sheet;
	g_return_if_fail (pane != NULL);
	sheet = scg_sheet (pane->simple.scg);
	g_return_if_fail (0 <= new_first_row && new_first_row < gnm_sheet_get_max_rows (sheet));

	if (pane->first.row != new_first_row) {
		GocCanvas * const canvas = GOC_CANVAS(pane);
		gint64 const row_offset = bar_set_top_row (pane, new_first_row);
		gint64 col_offset = pane->first_offset.x;

		gnm_pane_compute_visible_region (pane, FALSE);
		goc_canvas_scroll_to (canvas, col_offset / canvas->pixels_per_unit, row_offset / canvas->pixels_per_unit);
		gnm_pane_update_inital_top_left (pane);
	}
}
