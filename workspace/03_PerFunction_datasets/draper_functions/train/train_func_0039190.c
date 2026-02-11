isl_qpolynomial_bound_on_domain_range(__isl_take isl_basic_set *bset,
	__isl_take isl_qpolynomial *poly, struct isl_bound *bound)
{
	struct range_data data;
	int r;

	data.pwf = bound->pwf;
	data.pwf_tight = bound->pwf_tight;
	data.tight = bound->check_tight;
	if (bound->type == isl_fold_min)
		data.sign = -1;
	else
		data.sign = 1;

	r = qpolynomial_bound_on_domain_range(bset, poly, &data);

	bound->pwf = data.pwf;
	bound->pwf_tight = data.pwf_tight;

	return r;
}
