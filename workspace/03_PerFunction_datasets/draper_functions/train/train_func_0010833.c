gnm_cell_is_array (GnmCell const *cell)
{
	return cell != NULL && gnm_cell_has_expr (cell) &&
		(gnm_expr_top_is_array_corner (cell->base.texpr) ||
		 gnm_expr_top_is_array_elem (cell->base.texpr, NULL, NULL));
}
