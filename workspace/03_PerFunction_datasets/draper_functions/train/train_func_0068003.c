isl_union_pw_qpolynomial_bound(
	__isl_take isl_union_pw_qpolynomial *upwqp,
	enum isl_fold type, int *tight)
{
	isl_space *dim;
	struct isl_union_bound_data data = { type, 1, NULL };

	if (!upwqp)
		return NULL;

	if (!tight)
		data.tight = 0;

	dim = isl_union_pw_qpolynomial_get_space(upwqp);
	data.res = isl_union_pw_qpolynomial_fold_zero(dim, type);
	if (isl_union_pw_qpolynomial_foreach_pw_qpolynomial(upwqp,
						    &bound_pw, &data) < 0)
		goto error;

	isl_union_pw_qpolynomial_free(upwqp);
	if (tight)
		*tight = data.tight;

	return data.res;
error:
	isl_union_pw_qpolynomial_free(upwqp);
	isl_union_pw_qpolynomial_fold_free(data.res);
	return NULL;
}
