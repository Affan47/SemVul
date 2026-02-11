paste_cell (int target_col, int target_row,
	    GnmCellCopy const *src,
	    const struct paste_cell_data *dat)
{
	Sheet *dst_sheet = dat->pt->sheet;
	int paste_flags = dat->pt->paste_flags;

	if (paste_flags & PASTE_OPER_MASK)
		paste_cell_with_operation (dst_sheet, target_col, target_row,
					   &dat->rinfo, src, paste_flags);
	else {
		GnmCell *dst = sheet_cell_fetch (dst_sheet, target_col, target_row);
		if (NULL != src->texpr && (paste_flags & PASTE_CONTENTS)) {
			GnmExprTop const *relo = gnm_expr_top_relocate (
				src->texpr, &dat->rinfo, FALSE);
			if (paste_flags & PASTE_TRANSPOSE) {
				GnmExprTop const *trelo =
					gnm_expr_top_transpose (relo ? relo : src->texpr);
				if (trelo) {
					if (relo)
						gnm_expr_top_unref (relo);
					relo = trelo;
				}
			} else if (!relo && gnm_expr_top_is_array_corner (src->texpr)) {

				relo = gnm_expr_top_new (gnm_expr_copy (src->texpr->expr));
			}
			gnm_cell_set_expr_and_value (dst, relo ? relo : src->texpr,
						 value_dup (src->val), TRUE);
			if (NULL != relo)
				gnm_expr_top_unref (relo);
		} else {
			GnmValue *newval = NULL;
			GnmValue const *oldval = src->val;

			if (dat->translate_dates && oldval && VALUE_IS_FLOAT (oldval)) {
				GOFormat const *fmt = VALUE_FMT (oldval)
					? VALUE_FMT (oldval)
					: gnm_style_get_format (gnm_cell_get_style (dst));
				if (go_format_is_date (fmt) > 0) {
					gnm_float fnew = go_date_conv_translate
						(value_get_as_float (oldval),
						 dat->cr->date_conv,
						 workbook_date_conv (dst_sheet->workbook));
					newval = value_new_float (fnew);
					value_set_fmt (newval, VALUE_FMT (oldval));
				}
			}

			if (!newval)
				newval = value_dup (src->val);
			gnm_cell_set_value (dst, newval);
		}
	}
}
