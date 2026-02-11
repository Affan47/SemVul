pg_get_col_offset (GnmPreviewGrid *pg, int const x, int *col_origin)
{
	int col   = 0;
	int pixel = 1;
	int w;

	g_return_val_if_fail (pg != NULL, 0);

	do {
		w = pg->defaults.col_width;
		if (x <= (pixel + w) || w == 0) {
			if (col_origin)
				*col_origin = pixel;
			return col;
		}
		pixel += w;
	} while (++col < gnm_sheet_get_max_cols (pg->sheet));

	if (col_origin)
		*col_origin = pixel;

	return gnm_sheet_get_last_col (pg->sheet);
}
