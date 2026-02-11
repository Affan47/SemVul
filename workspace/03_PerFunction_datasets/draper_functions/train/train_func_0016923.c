bernstein_coefficients_factors(
	__isl_take isl_basic_set *bset,
	__isl_take isl_qpolynomial *poly, struct bernstein_data *data, int *tight)
{
	isl_factorizer *f;
	isl_set *set;
	isl_pw_qpolynomial *pwqp;
	isl_pw_qpolynomial_fold *pwf;

	f = isl_basic_set_factorizer(bset);
	if (!f)
		goto error;
	if (f->n_group == 0) {
		isl_factorizer_free(f);
		return  bernstein_coefficients_base(bset, poly, data, tight);
	}

	set = isl_set_from_basic_set(bset);
	pwqp = isl_pw_qpolynomial_alloc(set, poly);
	pwqp = isl_pw_qpolynomial_morph_domain(pwqp, isl_morph_copy(f->morph));

	pwf = bernstein_coefficients_recursive(pwqp, f->n_group, f->len, data,
						tight);

	isl_factorizer_free(f);

	return pwf;
error:
	isl_basic_set_free(bset);
	isl_qpolynomial_free(poly);
	return NULL;
}
