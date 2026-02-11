SetMatrixSize_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GelETree *n;
	long w,h;

	if G_UNLIKELY ( ! check_argument_matrix_or_null (a, 0, "SetMatrixSize"))
		return NULL;
	if G_UNLIKELY ( ! check_argument_nonnegative_integer (a, 1, "SetMatrixSize"))
		return NULL;
	if G_UNLIKELY ( ! check_argument_nonnegative_integer (a, 2, "SetMatrixSize"))
		return NULL;

	w = gel_get_nonnegative_integer (a[1]->val.value, "SetMatrixSize");
	if G_UNLIKELY (w < 0)
		return NULL;
	h = gel_get_nonnegative_integer (a[2]->val.value, "SetMatrixSize");
	if G_UNLIKELY (h < 0)
		return NULL;

	if (w == 0 || h == 0)
		return gel_makenum_null ();

	n = gel_stealnode (a[0]);
	if (n->type == GEL_NULL_NODE) {
		GelMatrixW *m;

		n->type = GEL_MATRIX_NODE;
		n->mat.matrix = m = gel_matrixw_new();
		n->mat.quoted = FALSE;
		gel_matrixw_set_size (m, h, w);


		m->rref = 1;

		m->cached_value_only = 1;
		m->value_only = 1;
		m->cached_value_only_real = 1;
		m->value_only_real = 1;
		m->cached_value_only_rational = 1;
		m->value_only_rational = 1;
		m->cached_value_only_integer = 1;
		m->value_only_integer = 1;
		m->cached_value_or_bool_only = 1;
		m->value_or_bool_only = 1;
	} else {
		gel_matrixw_set_size (n->mat.matrix, h, w);
	}
	return n;
}
