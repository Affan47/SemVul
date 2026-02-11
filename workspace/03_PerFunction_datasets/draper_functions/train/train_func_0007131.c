latex2e_find_vline (int col, int row, Sheet *sheet, GnmStyleElement which_border)
{

	GnmStyleBorderType result = latex2e_find_this_vline (col, row, sheet, which_border);
	GnmCellPos pos;
	GnmRange const * range;

	if (result == GNM_STYLE_BORDER_NONE)
		return GNM_STYLE_BORDER_NONE;

	pos.col = col;
	pos.row = row;
	range = gnm_sheet_merge_contains_pos (sheet, &pos);

	if (range) {
		if ((which_border == MSTYLE_BORDER_LEFT && col == range->start.col)
		    || (which_border == MSTYLE_BORDER_RIGHT&& col == range->end.col))
			return result;
		else
			return GNM_STYLE_BORDER_NONE;
	}
	return result;
}
