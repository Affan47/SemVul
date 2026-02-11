ExactDivision_op (GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	mpz_ptr numa, numb;
	mpz_t ret;
	mpw_t retw;

	if (a[0]->type == GEL_MATRIX_NODE ||
	    a[1]->type == GEL_MATRIX_NODE)
		return gel_apply_func_to_matrixen (ctx, a[0], a[1], ExactDivision_op, "ExactDivision", exception);

	if G_UNLIKELY ( ! check_argument_integer (a, 0, "ExactDivision") ||
			! check_argument_integer (a, 1, "ExactDivision"))
		return NULL;

	numa = mpw_peek_real_mpz (a[0]->val.value);
	numb = mpw_peek_real_mpz (a[1]->val.value);

	if (mpz_sgn (numb) == 0) {
		gel_errorout (_("Division by zero!"));

		return NULL;
	}

	mpz_init (ret);
	mpz_divexact (ret, numa, numb);

	mpw_init (retw);
	mpw_set_mpz_use (retw, ret);

	return gel_makenum (retw);
}
