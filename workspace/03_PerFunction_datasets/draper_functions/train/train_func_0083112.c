range_clip_to_finite (GnmRange *range, Sheet *sheet)
{
	GnmRange extent;


	extent = sheet_get_extent (sheet, FALSE, TRUE);
	if (range->end.col >= gnm_sheet_get_max_cols (sheet) - 1)
		range->end.col = extent.end.col;
	if (range->end.row >= gnm_sheet_get_max_rows (sheet) - 1)
		range->end.row = extent.end.row;
}
