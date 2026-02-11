e_table_item_row_diff (ETableItem *eti,
                       gint start_row,
                       gint end_row)
{
	gint height_extra = eti->horizontal_draw_grid ? 1 : 0;

	if (start_row < 0)
		start_row = 0;
	if (end_row > eti->rows)
		end_row = eti->rows;

	if (eti->uniform_row_height) {
		return ((end_row - start_row) * (ETI_ROW_HEIGHT (eti, -1) + height_extra));
	} else {
		gint row, total;
		total = 0;
		for (row = start_row; row < end_row; row++)
			total += ETI_ROW_HEIGHT (eti, row) + height_extra;

		return total;
	}
}
