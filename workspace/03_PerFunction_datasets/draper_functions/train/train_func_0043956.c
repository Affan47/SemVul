sqrt_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	if (a[0]->type == GEL_FUNCTION_NODE ||
	    a[0]->type == GEL_IDENTIFIER_NODE) {
		return gel_function_from_function (sqrt_function, a[0]);
	}

	if(a[0]->type==GEL_MATRIX_NODE)
		return gel_apply_func_to_matrix(ctx,a[0],sqrt_op,"sqrt", exception);

	if G_UNLIKELY ( ! check_argument_number (a, 0, "sqrt"))
		return NULL;
	if (ctx->modulo != NULL) {
		GelETree *arg[3];
		GelETree *ret;
		gboolean is_prime;
		mpz_ptr num;
		GelEFunc *SqrtModPrime;
		static GelToken *SqrtModPrime_id = NULL;

		if G_UNLIKELY ( ! check_argument_integer (a, 0, "sqrt"))
			return NULL;

		num = mpw_peek_real_mpz (ctx->modulo);
		is_prime = mympz_is_prime (num, -1);

		if G_UNLIKELY ( ! is_prime) {
			gel_errorout (_("%s: square root for composite moduli "
					"is not yet implemented"), "sqrt");
			return NULL;
		}
		if G_UNLIKELY (SqrtModPrime_id == NULL)
			SqrtModPrime_id = d_intern ("SqrtModPrime");
		SqrtModPrime = d_lookup_only_global (SqrtModPrime_id);
		if G_UNLIKELY (SqrtModPrime == NULL) {
			gel_errorout (_("%s: Cannot find square root function "
					"for prime moduli"), "sqrt");
			return NULL;
		}
		arg[0] = a[0];
		arg[1] = gel_makenum (ctx->modulo);
		arg[2] = NULL;
		ret = gel_funccall (ctx, SqrtModPrime, arg, 2);
		gel_freetree (arg[1]);

		return ret;
	} else {
		mpw_t fr;

		mpw_init(fr);
		mpw_sqrt(fr,a[0]->val.value);
		return gel_makenum_use(fr);
	}
}
