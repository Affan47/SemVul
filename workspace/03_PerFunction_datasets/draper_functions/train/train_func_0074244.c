isl_upoly_sgn(__isl_keep struct isl_upoly *up)
{
	struct isl_upoly_cst *cst;

	if (!up)
		return 0;
	if (!isl_upoly_is_cst(up))
		return 0;

	cst = isl_upoly_as_cst(up);
	if (!cst)
		return 0;

	return isl_int_sgn(cst->n);
}
