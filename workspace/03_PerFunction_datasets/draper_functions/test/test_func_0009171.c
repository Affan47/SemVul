isl_qpolynomial_val_on_domain(
	__isl_take isl_space *domain, __isl_take isl_val *val)
{
	isl_qpolynomial *qp;
	struct isl_upoly_cst *cst;

	if (!domain || !val)
		goto error;

	qp = isl_qpolynomial_alloc(isl_space_copy(domain), 0,
					isl_upoly_zero(domain->ctx));
	if (!qp)
		goto error;

	cst = isl_upoly_as_cst(qp->upoly);
	isl_int_set(cst->n, val->n);
	isl_int_set(cst->d, val->d);

	isl_space_free(domain);
	isl_val_free(val);
	return qp;
error:
	isl_space_free(domain);
	isl_val_free(val);
	return NULL;
}
