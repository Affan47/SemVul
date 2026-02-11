odf_sheet_suggest_size (GsfXMLIn *xin, int *cols, int *rows)
{
	int c = GNM_MIN_COLS;
	int r = GNM_MIN_ROWS;

	while (c < *cols && c < GNM_MAX_COLS)
		c *= 2;

	while (r < *rows && r < GNM_MAX_ROWS)
		r *= 2;

	while (!gnm_sheet_valid_size (c, r))
		gnm_sheet_suggest_size (&c, &r);

	if (xin != NULL && (*cols > c || *rows > r))
		oo_warning (xin, _("The sheet size of %i columns and %i rows used in this file "
			      "exceeds Gnumeric's maximum supported sheet size"), *cols, *rows);

	*cols = c;
	*rows = r;
}
