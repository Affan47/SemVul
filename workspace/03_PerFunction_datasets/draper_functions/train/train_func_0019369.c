isl_basic_set_multiplicative_call(
	__isl_take isl_basic_set *bset,
	__isl_give isl_pw_qpolynomial *(*fn)(__isl_take isl_basic_set *bset))
{
	int bounded;
	isl_morph *morph;
	isl_pw_qpolynomial *pwqp;

	if (!bset)
		return NULL;

	if (isl_basic_set_plain_is_empty(bset))
		return constant_on_domain(bset, 0);

	if (isl_basic_set_dim(bset, isl_dim_set) == 0)
		return constant_on_domain(bset, 1);

	bounded = isl_basic_set_is_bounded(bset);
	if (bounded < 0)
		goto error;
	if (!bounded)
		return constant_on_domain(bset, -1);

	if (bset->n_eq == 0)
		return compressed_multiplicative_call(bset, fn);

	morph = isl_basic_set_full_compression(bset);
	bset = isl_morph_basic_set(isl_morph_copy(morph), bset);

	pwqp = compressed_multiplicative_call(bset, fn);

	morph = isl_morph_dom_params(morph);
	morph = isl_morph_ran_params(morph);
	morph = isl_morph_inverse(morph);

	pwqp = isl_pw_qpolynomial_morph_domain(pwqp, morph);

	return pwqp;
error:
	isl_basic_set_free(bset);
	return NULL;
}
