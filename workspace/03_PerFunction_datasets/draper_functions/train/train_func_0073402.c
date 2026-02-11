cb_check_names (gpointer key, GnmNamedExpr *nexpr, ExcelWriteState *ewb)
{
	if (expr_name_is_active (nexpr))
		excel_write_prep_expr (ewb, nexpr->texpr);
}
