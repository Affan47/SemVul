calc_length (GnmValue   *bin)
{
	g_return_val_if_fail (bin != NULL, 0);
	g_return_val_if_fail (bin->type == VALUE_CELLRANGE, 0);

	return ((bin->v_range.cell.b.col - bin->v_range.cell.a.col + 1) *
		(bin->v_range.cell.b.row - bin->v_range.cell.a.row + 1));
}
