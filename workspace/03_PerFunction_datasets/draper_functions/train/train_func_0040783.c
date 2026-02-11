sheet_style_resize (Sheet *sheet, int cols, int rows)
{
	GnmStyleList *styles, *l;
	int old_cols = gnm_sheet_get_max_cols (sheet);
	int old_rows = gnm_sheet_get_max_rows (sheet);
	GnmRange save_range, new_full;


	range_init (&save_range, 0, 0,
		    MIN (cols, old_cols) - 1, MIN (rows, old_rows) - 1);
	styles = sheet_style_get_range (sheet, &save_range);


	sheet_style_shutdown (sheet);
	sheet_style_init_size (sheet, cols, rows);


	range_init (&new_full, 0, 0, cols - 1, rows - 1);
	for (l = styles; l; l = l->next) {
		GnmStyleRegion const *sr = l->data;
		GnmRange const *r = &sr->range;
		GnmStyle *style = sr->style;
		GnmRange newr;
		if (range_intersection (&newr, r, &new_full)) {
			gnm_style_ref (style);
			sheet_style_apply_range (sheet, &newr, style);
		}
	}

	style_list_free	(styles);
}
