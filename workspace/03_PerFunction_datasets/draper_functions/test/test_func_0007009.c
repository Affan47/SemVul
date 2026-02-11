ColumnsOf_op (GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GelETree *n;

	if (a[0]->type == GEL_NULL_NODE)
		return gel_makenum_null ();

	if G_UNLIKELY ( ! check_argument_matrix (a, 0, "ColumnsOf"))
		return NULL;

	GEL_GET_NEW_NODE (n);
	n->type = GEL_MATRIX_NODE;
	n->mat.matrix = gel_matrixw_columnsof (a[0]->mat.matrix);
	n->mat.quoted = FALSE;
	return n;
}
