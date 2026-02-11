isl_upoly_is_one(__isl_keep struct isl_upoly *up)
{
	struct isl_upoly_cst *cst;

	if (!up)
		return -1;
	if (!isl_upoly_is_cst(up))
		return 0;

	cst = isl_upoly_as_cst(up);
	if (!cst)
		return -1;

	return isl_int_eq(cst->n, cst->d) && isl_int_is_pos(cst->d);
}
