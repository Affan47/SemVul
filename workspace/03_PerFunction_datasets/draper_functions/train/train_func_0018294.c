isl_basic_set_opt_val(__isl_keep isl_basic_set *bset,
	int max, __isl_keep isl_aff *obj)
{
	isl_ctx *ctx;
	isl_val *res;
	enum isl_lp_result lp_res;

	if (!bset || !obj)
		return NULL;

	ctx = isl_aff_get_ctx(obj);
	res = isl_val_alloc(ctx);
	if (!res)
		return NULL;
	lp_res = isl_basic_set_opt(bset, max, obj, &res->n);
	return convert_lp_result(lp_res, res, max);
}
