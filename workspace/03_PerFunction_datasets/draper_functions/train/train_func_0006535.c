cb_clear_rendered_cells (G_GNUC_UNUSED gpointer ignored, GnmCell *cell)
{
	if (gnm_cell_get_rendered_value (cell) != NULL) {
		sheet_cell_queue_respan (cell);
		gnm_cell_unrender (cell);
	}
}
