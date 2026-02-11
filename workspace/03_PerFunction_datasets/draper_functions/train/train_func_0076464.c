sheet_colrow_group_ungroup (Sheet *sheet, GnmRange const *r,
			    gboolean is_cols, gboolean group)
{
	int i, new_max, start, end;
	int const step = group ? 1 : -1;

	g_return_val_if_fail (IS_SHEET (sheet), FALSE);


	if (group != sheet_colrow_can_group (sheet, r, is_cols))
		return FALSE;

	if (is_cols) {
		start = r->start.col;
		end = r->end.col;
	} else {
		start = r->start.row;
		end = r->end.row;
	}


	new_max = (is_cols ? &sheet->cols : &sheet->rows)->max_outline_level;
	for (i = start; i <= end; i++) {
		ColRowInfo *cri = sheet_colrow_fetch (sheet, i, is_cols);
		int const new_level = cri->outline_level + step;

		if (new_level >= 0) {
			colrow_set_outline (cri, new_level, FALSE);
			if (new_max < new_level)
				new_max = new_level;
		}
	}

	if (!group)
		new_max = sheet_colrow_fit_gutter (sheet, is_cols);

	sheet_colrow_gutter (sheet, is_cols, new_max);
	SHEET_FOREACH_VIEW (sheet, sv,
		sv_redraw_headers (sv, is_cols, !is_cols, NULL););

	return TRUE;
}
