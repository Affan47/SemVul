compressed_guarded_poly_bound(__isl_take isl_basic_set *bset,
	__isl_take isl_qpolynomial *poly, void *user)
{
	struct isl_bound *bound = (struct isl_bound *)user;
	int bounded;

	if (!bset || !poly)
		goto error;

	if (bset->ctx->opt->bound == ISL_BOUND_RANGE)
		return isl_qpolynomial_bound_on_domain_range(bset, poly, bound);

	bounded = isl_basic_set_is_bounded(bset);
	if (bounded < 0)
		goto error;
	if (bounded)
		return isl_qpolynomial_bound_on_domain_bernstein(bset, poly, bound);
	else
		return isl_qpolynomial_bound_on_domain_range(bset, poly, bound);
error:
	isl_basic_set_free(bset);
	isl_qpolynomial_free(poly);
	return -1;
}
