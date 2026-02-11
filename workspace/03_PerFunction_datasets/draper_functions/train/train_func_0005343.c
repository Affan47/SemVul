style_row_init (GnmBorder const * * *prev_vert,
		GnmStyleRow *sr, GnmStyleRow *next_sr,
		int start_col, int end_col, gpointer mem, gboolean hide_grid)
{
	int n, col;
	GnmBorder const *none = hide_grid ? NULL : gnm_style_border_none ();


	n = end_col - start_col + 3;
	sr->vertical	 = mem;
	sr->vertical	-= start_col-1;
	sr->top		 = sr->vertical + n;
	sr->bottom	 = sr->top + n;
	next_sr->top	 = sr->bottom;
	next_sr->bottom	 = next_sr->top + n;
	next_sr->vertical = next_sr->bottom + n;
	*prev_vert	 = next_sr->vertical + n;
	sr->styles	 = ((GnmStyle const **) (*prev_vert + n));
	next_sr->styles	 = sr->styles + n;
	sr->start_col	 = next_sr->start_col = start_col;
	sr->end_col	 = next_sr->end_col   = end_col;
	sr->hide_grid    = next_sr->hide_grid = hide_grid;


	for (col = start_col-1 ; col <= end_col+1; ++col)
		(*prev_vert)[col] = sr->top[col] = none;
	sr->vertical	 [start_col-1] = sr->vertical	   [end_col+1] =
	next_sr->vertical[start_col-1] = next_sr->vertical[end_col+1] =
	next_sr->top	 [start_col-1] = next_sr->top	   [end_col+1] =
	next_sr->bottom	 [start_col-1] = next_sr->bottom  [end_col+1] = none;
}
