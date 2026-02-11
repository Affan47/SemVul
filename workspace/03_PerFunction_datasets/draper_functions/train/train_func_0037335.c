reloc_range (GnmExprRelocateInfo const *rinfo,
	     Sheet const *start_sheet, Sheet const *end_sheet,
	     GnmRange *rng)
{
	GnmRange t, b, l, r;
	gboolean start, end;

	if (start_sheet != end_sheet ||
	    start_sheet != rinfo->origin_sheet)
		return FALSE;

	t.start.col = b.start.col = l.start.col = l.end.col   = rng->start.col;
	t.end.col   = b.end.col   = r.start.col = r.end.col   = rng->end.col;
	t.start.row = t.end.row   = l.start.row = r.start.row = rng->start.row;
	b.start.row = b.end.row   = l.end.row   = r.end.row   = rng->end.row;

	start = range_contained (&t, &rinfo->origin);
	end   = range_contained (&b, &rinfo->origin);
	if (start && end) {
		rng->start.col += rinfo->col_offset;
		rng->end.col   += rinfo->col_offset;
		rng->start.row += rinfo->row_offset;
		rng->end.row   += rinfo->row_offset;
		return TRUE;
	}

	if (rinfo->col_offset == 0) {
		if (start && rinfo->row_offset < range_height (rng)) {
			rng->start.row += rinfo->row_offset;
			return TRUE;
		}
		if (end && rinfo->row_offset > -range_height (rng)) {


			if (rinfo->reloc_type == GNM_EXPR_RELOCATE_ROWS &&
			    rinfo->row_offset >= gnm_sheet_get_max_rows (end_sheet))
				rng->end.row  = rinfo->origin.start.row - 1;
			else
				rng->end.row += rinfo->row_offset;
			return TRUE;
		}
	}

	if (rinfo->row_offset == 0) {
		if (range_contained (&l, &rinfo->origin) &&
		    rinfo->col_offset < range_width (rng)) {
			rng->start.col += rinfo->col_offset;
			return TRUE;
		}
		if (range_contained (&r, &rinfo->origin) &&
		    rinfo->col_offset > -range_width (rng)) {


			if (rinfo->reloc_type == GNM_EXPR_RELOCATE_COLS &&
			    rinfo->col_offset >= gnm_sheet_get_max_cols (end_sheet))
				rng->end.col  = rinfo->origin.start.col - 1;
			else
				rng->end.col += rinfo->col_offset;
			return TRUE;
		}
	}

	return FALSE;
}
