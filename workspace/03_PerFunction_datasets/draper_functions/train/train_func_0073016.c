odf_func_true_handler (G_GNUC_UNUSED GnmConventions const *convs,
		       G_GNUC_UNUSED Workbook *scope, GnmExprList *args)
{
	return args ? NULL : gnm_expr_new_constant (value_new_bool (TRUE));
}
