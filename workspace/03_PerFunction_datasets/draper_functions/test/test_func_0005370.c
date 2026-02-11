rref_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GelETree *n;
	if G_UNLIKELY ( ! check_argument_value_only_matrix (a, 0, "rref"))
		return NULL;

	GEL_GET_NEW_NODE(n);
	n->type = GEL_MATRIX_NODE;
	n->mat.matrix = gel_matrixw_copy(a[0]->mat.matrix);
	if ( ! n->mat.matrix->rref) {
		gel_value_matrix_gauss (ctx, n->mat.matrix, TRUE, FALSE, FALSE, FALSE, NULL, NULL);
	}
	n->mat.quoted = FALSE;
	return n;
}
