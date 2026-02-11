reloc_cellrange (RelocInfoInternal const *rinfo, GnmValueRange const *v,
		 gboolean sticky_end)
{
	GnmRange r;
	Sheet   *start_sheet, *end_sheet;
	GnmSheetSize const *start_ss, *end_ss;
	gboolean full_col, full_row;
	gboolean full_col_begin, full_row_begin;


	reloc_normalize_cellref (rinfo, &v->cell.a, &start_sheet, &r.start);
	reloc_normalize_cellref (rinfo, &v->cell.b, &end_sheet,   &r.end);

	if (NULL == v->cell.b.sheet)
		end_sheet = start_sheet;
	start_ss = gnm_sheet_get_size2 (start_sheet, rinfo->details->pos.wb);
	end_ss = gnm_sheet_get_size2 (end_sheet, rinfo->details->pos.wb);

	full_col = sticky_end && r.end.row >= start_ss->max_rows - 1;
	full_col_begin = full_col && r.start.row == 0;

	full_row = sticky_end && r.end.col >= start_ss->max_cols - 1;
	full_row_begin = full_row && r.start.col == 0;

	if (reloc_range (rinfo->details, start_sheet, end_sheet, &r) ||
	    rinfo->from_inside) {
		GnmRangeRef res = v->cell;

		if (full_col)
			r.end.row = start_ss->max_rows - 1;
		if (full_col_begin)
			r.start.row = 0;
		if (full_row)
			r.end.col = start_ss->max_cols - 1;
		if (full_row_begin)
			r.start.col = 0;

		if (reloc_restore_cellref (rinfo, start_ss, &r.start, &res.a) ||
		    reloc_restore_cellref (rinfo, end_ss,   &r.end,   &res.b))
			return gnm_expr_new_constant (value_new_error_REF (NULL));
		if (gnm_rangeref_equal (&res, &v->cell))
			return NULL;
		return gnm_expr_new_constant (value_new_cellrange_unsafe (&res.a, &res.b));
	}

	return NULL;
}
