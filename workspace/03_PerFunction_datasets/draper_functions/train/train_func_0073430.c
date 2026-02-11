sheet_autofill_internal (Sheet *sheet, gboolean singleton,
			 int base_col, int base_row,
			 int w, int h,
			 int end_col, int end_row,
			 gboolean doit)
{
	int series = 0;
	int right_col = MAX (base_col, end_col);
	int bottom_row = MAX (base_row, end_row);
	GString *res = NULL;
	GnmCellPos pos;
	GnmRange const *mr;

	g_return_val_if_fail (IS_SHEET (sheet), NULL);

	if (!doit)
		res = g_string_new (NULL);

	pos.col = base_col;
	pos.row = base_row;

	if (base_col > end_col || base_row > end_row) {
		if (base_col != end_col + w - 1) {

			while (series < h) {
				add_item (res,
					  sheet_autofill_dir (sheet, singleton,
							      base_col, base_row - series,
							      w, ABS (base_col - (end_col - 1)),
							      -1, 0,
							      right_col, bottom_row,
							      doit),
					  "\n");

				pos.row = base_row - series;
				mr = gnm_sheet_merge_contains_pos (sheet, &pos);
				series += mr ? range_height (mr) : 1;
			}
		} else {

			while (series < w) {
				add_item (res,
					  sheet_autofill_dir (sheet, singleton,
							      base_col - series, base_row,
							      h, ABS (base_row - (end_row - 1)),
							      0, -1,
							      right_col, bottom_row,
							      doit),
					  " | ");

				pos.col = base_col - series;
				mr = gnm_sheet_merge_contains_pos (sheet, &pos);
				series += mr ? range_width (mr) : 1;
			}
		}
	} else {
		if (end_col != base_col + w - 1) {

			while (series < h) {
				add_item (res,
					  sheet_autofill_dir (sheet, singleton,
							      base_col, base_row + series,
							      w, ABS (base_col - (end_col + 1)),
							      1, 0,
							      right_col, bottom_row,
							      doit),
					  "\n");

				pos.row = base_row + series;
				mr = gnm_sheet_merge_contains_pos (sheet, &pos);
				series += mr ? range_height (mr) : 1;
			}
		} else {

			while (series < w) {
				add_item (res,
					  sheet_autofill_dir (sheet, singleton,
							      base_col + series, base_row,
							      h, ABS (base_row - (end_row + 1)),
							      0, 1,
							      right_col, bottom_row,
							      doit),
					  " | ");
				pos.col = base_col + series;
				mr = gnm_sheet_merge_contains_pos (sheet, &pos);
				series += mr ? range_width (mr) : 1;
			}
		}
	}

	return res;
}
