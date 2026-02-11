knot_copy_key_params(const knot_key_params_t *src, knot_key_params_t *dst)
{
	if (src == NULL || dst == NULL) {
		return KNOT_EINVAL;
	}

	int ret = 0;

	if (src->name != NULL) {
		dst->name = knot_dname_copy(src->name);
		if (dst->name == NULL) {
			ret += -1;
		}
	}

	dst->algorithm = src->algorithm;
	dst->keytag = src->keytag;

	ret += knot_binary_dup(&src->secret, &dst->secret);

	ret += knot_binary_dup(&src->modulus, &dst->modulus);
	ret += knot_binary_dup(&src->public_exponent, &dst->public_exponent);
	ret += knot_binary_dup(&src->private_exponent, &dst->private_exponent);
	ret += knot_binary_dup(&src->prime_one, &dst->prime_one);
	ret += knot_binary_dup(&src->prime_two, &dst->prime_two);
	ret += knot_binary_dup(&src->exponent_one, &dst->exponent_one);
	ret += knot_binary_dup(&src->exponent_two, &dst->exponent_two);
	ret += knot_binary_dup(&src->coefficient, &dst->coefficient);

	ret += knot_binary_dup(&src->prime, &dst->prime);
	ret += knot_binary_dup(&src->subprime, &dst->subprime);
	ret += knot_binary_dup(&src->base, &dst->base);
	ret += knot_binary_dup(&src->private_value, &dst->private_value);
	ret += knot_binary_dup(&src->public_value, &dst->public_value);

	ret += knot_binary_dup(&src->private_key, &dst->private_key);

	if (ret < 0) {
		knot_free_key_params(dst);
		return KNOT_ENOMEM;
	}

	return KNOT_EOK;
}
