sheet_colrow_get_default (Sheet const *sheet, gboolean is_cols)
{
	g_return_val_if_fail (IS_SHEET (sheet), NULL);

	return is_cols ? &sheet->cols.default_style : &sheet->rows.default_style;
}
