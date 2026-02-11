sheet_cell_remove (Sheet *sheet, GnmCell *cell,
		   gboolean redraw, gboolean queue_recalc)
{
	g_return_if_fail (cell != NULL);
	g_return_if_fail (IS_SHEET (sheet));


	if (redraw) {
		sheet_redraw_region (sheet,
				     cell->pos.col, cell->pos.row,
				     cell->pos.col, cell->pos.row);
		sheet_flag_status_update_cell (cell);
	}

	sheet_cell_destroy (sheet, cell, queue_recalc);
}
