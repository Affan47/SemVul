QuadraticFormula_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GelETree *n;
	GelMatrixW *m;
	GelMatrix *nm;

	mpw_ptr aa, bb, cc;
	mpw_t r1, r2;

	if G_UNLIKELY (a[0]->type == GEL_NULL_NODE)
		return gel_makenum_null ();

	if G_UNLIKELY ( ! check_poly(a,1,"QuadraticFormula",TRUE))
		return NULL;

	m = a[0]->mat.matrix;

	if G_UNLIKELY (gel_matrixw_elements (m) != 3 ||
		       mpw_zero_p (gel_matrixw_index(m,2,0)->val.value)) {
		gel_errorout (_("%s: argument 1 must be a quadratic polynomial"),
			      "QuadraticFormula");
		return NULL;
	}

	aa = gel_matrixw_index(m,2,0)->val.value;
	bb = gel_matrixw_index(m,1,0)->val.value;
	cc = gel_matrixw_index(m,0,0)->val.value;

	mpw_init (r1);
	mpw_init (r2);

	if (mpw_zero_p (cc)) {
		mpw_div (r1, bb, aa);
		mpw_neg (r1, r1);
		mpw_set_ui (r2, 0);
	} else if (mpw_zero_p (bb)) {
		mpw_mul (r1, aa, cc);
		mpw_neg (r1, r1);
		mpw_sqrt (r1, r1);
		mpw_div (r1, r1, aa);
		mpw_neg (r2, r1);
	} else {
		mpw_mul (r1, bb, bb);
		mpw_mul (r2, aa, cc);
		mpw_mul_ui (r2, r2, 4);
		mpw_sub (r1, r1, r2);
		mpw_sqrt (r1, r1);


		if (mpw_re_sgn (r1) != mpw_re_sgn (bb)) {
			mpw_neg (r1, r1);
		}

		mpw_add (r1, r1, bb);
		mpw_div_ui (r1, r1, 2);
		mpw_neg (r1, r1);


		mpw_div (r2, cc, r1);

		mpw_div (r1, r1, aa);
	}

	nm = gel_matrix_new ();
	gel_matrix_set_size (nm, 1, 2, FALSE );
	gel_matrix_index (nm, 0, 0) = gel_makenum_use (r1);
	gel_matrix_index (nm, 0, 1) = gel_makenum_use (r2);

	GEL_GET_NEW_NODE (n);
	n->type = GEL_MATRIX_NODE;
	n->mat.matrix = gel_matrixw_new_with_matrix_value_only (nm);
	n->mat.quoted = FALSE;

	return n;
}
