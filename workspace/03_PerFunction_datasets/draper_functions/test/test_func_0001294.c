BesselY0_op (GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	mpfr_ptr num;
	mpfr_t tmp;
	mpfr_t ret;
	mpw_t retw;

	if (a[0]->type == GEL_FUNCTION_NODE ||
	    a[0]->type == GEL_IDENTIFIER_NODE) {
		return gel_function_from_function (BesselY0_function, a[0]);
	}

	if (a[0]->type == GEL_MATRIX_NODE)
		return gel_apply_func_to_matrix (ctx, a[0], BesselY0_op, "BesselY0", exception);

	if G_UNLIKELY ( ! check_argument_number (a, 0, "BesselY0"))
		return NULL;
	if G_UNLIKELY (mpw_is_complex (a[0]->val.value)) {
		gel_errorout (_("%s: Not implemented (yet) for complex values"),
			      "BesselY0");
		return NULL;
	}
	if G_UNLIKELY (mpw_sgn (a[0]->val.value) <= 0) {
		gel_errorout (_("%s: Bessel functions of second kind not defined for nonpositive real numbers"),
			      "BesselY0");
		return NULL;
	}

	MPW_MPF_REAL (num, a[0]->val.value, tmp);

	mpfr_init (ret);
	mpfr_y0 (ret, num, GMP_RNDN);

	MPW_MPF_KILL (num, tmp);

	mpw_init (retw);
	mpw_set_mpf_use (retw, ret);

	return gel_makenum (retw);
}
