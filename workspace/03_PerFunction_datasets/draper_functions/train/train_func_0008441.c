isl_upoly_cst_scale_val(
	__isl_take struct isl_upoly *up, __isl_keep isl_val *v)
{
	struct isl_upoly_cst *cst;

	if (isl_upoly_is_zero(up))
		return up;

	up = isl_upoly_cow(up);
	if (!up)
		return NULL;

	cst = isl_upoly_as_cst(up);

	isl_int_mul(cst->n, cst->n, v->n);
	isl_int_mul(cst->d, cst->d, v->d);
	isl_upoly_cst_reduce(cst);

	return up;
}
