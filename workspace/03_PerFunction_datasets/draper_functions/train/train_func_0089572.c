knot_tsig_key_from_params(const knot_key_params_t *params,
                              knot_tsig_key_t *key)
{
	if (!params || !params->name || params->secret.size == 0) {
		return KNOT_EINVAL;
	}

	int result = knot_binary_dup(&params->secret, &key->secret);
	if (result != KNOT_EOK) {
		return result;
	}

	key->name = knot_dname_copy(params->name);

	key->algorithm = params->algorithm;

	return KNOT_EOK;
}
