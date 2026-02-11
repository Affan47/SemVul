cb_set_array_value (GnmCellIter const *iter, gpointer user)
{
	GnmValue const *value = user;
	GnmCell *cell = iter->cell;
	int x, y;


	if (gnm_cell_expr_is_linked (cell))
		dependent_unlink (GNM_CELL_TO_DEP (cell));

	if (!gnm_expr_top_is_array_elem (cell->base.texpr, &x, &y))
		return NULL;

	gnm_expr_top_unref (cell->base.texpr);
	cell->base.texpr = NULL;
	value_release (cell->value);
	cell->value = value_dup (value_area_get_x_y (value, x, y, NULL));

	return NULL;
}
