knot_tsig_create_key(const char *name, int algorithm,
                         const char *b64secret, knot_tsig_key_t *key)
{
	if (!name || !b64secret || !key) {
		return KNOT_EINVAL;
	}

	knot_dname_t *dname;
	dname = knot_dname_from_str(name);
	if (!dname) {
		return KNOT_ENOMEM;
	}

	knot_binary_t secret;
	int result = knot_binary_from_base64(b64secret, &secret);
	if (result != KNOT_EOK) {
		knot_dname_free(&dname);
		return result;
	}

	key->name = dname;
	key->algorithm = algorithm;
	key->secret = secret;

	return KNOT_EOK;
}
