isl_qpolynomial_cst_sign(__isl_keep isl_qpolynomial *qp)
{
	struct isl_upoly_cst *cst;

	cst = isl_upoly_as_cst(qp->upoly);
	if (!cst)
		return 0;

	return isl_int_sgn(cst->n) < 0 ? -1 : 1;
}
