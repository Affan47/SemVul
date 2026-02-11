isl_upoly_cst_mul_isl_int(
	__isl_take struct isl_upoly *up, isl_int v)
{
	struct isl_upoly_cst *cst;

	if (isl_upoly_is_zero(up))
		return up;

	up = isl_upoly_cow(up);
	if (!up)
		return NULL;

	cst = isl_upoly_as_cst(up);

	isl_int_mul(cst->n, cst->n, v);

	return up;
}
