IsIn_op (GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	if G_UNLIKELY ( ! check_argument_matrix_or_null (a, 1, "IsIn"))
		return NULL;

	if (a[1]->type == GEL_NULL_NODE)
		return gel_makenum_bool (FALSE);

	return gel_makenum_bool (symbolic_isinmatrix (a[0], a[1]->mat.matrix));
}
