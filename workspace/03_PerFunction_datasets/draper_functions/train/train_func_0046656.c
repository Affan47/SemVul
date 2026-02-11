gnumeric_averageif (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	GnmRange rs;
	Sheet *start_sheet, *end_sheet;
	SumIfClosure res;
	GnmValue *problem;
	GODateConventions const *date_conv =
		workbook_date_conv (ei->pos->sheet->workbook);


	if (argv[0]->type != VALUE_CELLRANGE ||
	    (!VALUE_IS_NUMBER (argv[1]) && !VALUE_IS_STRING (argv[1])) ||
	    (argv[2] != NULL && argv[2]->type != VALUE_CELLRANGE))
	        return value_new_error_VALUE (ei->pos);

	gnm_rangeref_normalize (&argv[0]->v_range.cell, ei->pos,
				&start_sheet, &end_sheet,
				&rs);
	if (start_sheet != end_sheet)
		return value_new_error_VALUE (ei->pos);

	if (argv[2]) {
		GnmRange ra;

		gnm_rangeref_normalize (&argv[2]->v_range.cell, ei->pos,
					&res.target_sheet, &end_sheet,
					&ra);
		if (res.target_sheet != end_sheet)
			return value_new_error_VALUE (ei->pos);

		res.offset_col = ra.start.col - rs.start.col;
		res.offset_row = ra.start.row - rs.start.row;
	} else
		res.target_sheet = NULL;

	res.sum = 0.;
	res.count = 0;
	res.crit = parse_criteria (argv[1], date_conv);
	problem = sheet_foreach_cell_in_range
		(start_sheet, res.crit->iter_flags,
		 rs.start.col, rs.start.row, rs.end.col, rs.end.row,
		 (CellIterFunc) &cb_sumif, &res);
	free_criteria (res.crit);

	if (NULL != problem)
	        return value_new_error_VALUE (ei->pos);
	if (res.count == 0)
		return value_new_error_DIV0 (ei->pos);
	return value_new_float (res.sum/res.count);
}
