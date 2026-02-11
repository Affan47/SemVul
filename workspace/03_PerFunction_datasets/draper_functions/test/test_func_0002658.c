normalize_constraint(__isl_take isl_vec *v,
	int *tightened)
{
	isl_ctx *ctx;

	if (!v)
		return NULL;
	ctx = isl_vec_get_ctx(v);
	isl_seq_gcd(v->el + 1, v->size - 1, &ctx->normalize_gcd);
	if (isl_int_is_zero(ctx->normalize_gcd))
		return v;
	if (isl_int_is_one(ctx->normalize_gcd))
		return v;
	v = isl_vec_cow(v);
	if (!v)
		return NULL;
	if (tightened && !isl_int_is_divisible_by(v->el[0], ctx->normalize_gcd))
		*tightened = 1;
	isl_int_fdiv_q(v->el[0], v->el[0], ctx->normalize_gcd);
	isl_seq_scale_down(v->el + 1, v->el + 1, ctx->normalize_gcd,
				v->size - 1);
	return v;
}
