gnm_cell_get_style (GnmCell const *cell)
{
	g_return_val_if_fail (cell != NULL, NULL);
	return sheet_style_get (cell->base.sheet,
				cell->pos.col,
				cell->pos.row);
}
