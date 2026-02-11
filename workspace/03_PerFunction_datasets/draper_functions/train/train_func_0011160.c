bernstein_coefficients_full_recursive(
	__isl_take isl_basic_set *bset,
	__isl_take isl_qpolynomial *poly, struct bernstein_data *data, int *tight)
{
	int i;
	int *len;
	unsigned nvar;
	isl_pw_qpolynomial_fold *pwf;
	isl_set *set;
	isl_pw_qpolynomial *pwqp;

	if (!bset || !poly)
		goto error;

	nvar = isl_basic_set_dim(bset, isl_dim_set);

	len = isl_alloc_array(bset->ctx, int, nvar);
	if (nvar && !len)
		goto error;

	for (i = 0; i < nvar; ++i)
		len[i] = 1;

	set = isl_set_from_basic_set(bset);
	pwqp = isl_pw_qpolynomial_alloc(set, poly);

	pwf = bernstein_coefficients_recursive(pwqp, nvar, len, data, tight);

	free(len);

	return pwf;
error:
	isl_basic_set_free(bset);
	isl_qpolynomial_free(poly);
	return NULL;
}
