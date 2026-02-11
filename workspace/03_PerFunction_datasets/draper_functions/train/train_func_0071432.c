openssldh_compare(const dst_key_t *key1, const dst_key_t *key2) {
	int status;
	DH *dh1, *dh2;

	dh1 = key1->keydata.dh;
	dh2 = key2->keydata.dh;

	if (dh1 == NULL && dh2 == NULL)
		return (ISC_TRUE);
	else if (dh1 == NULL || dh2 == NULL)
		return (ISC_FALSE);

	status = BN_cmp(dh1->p, dh2->p) ||
		 BN_cmp(dh1->g, dh2->g) ||
		 BN_cmp(dh1->pub_key, dh2->pub_key);

	if (status != 0)
		return (ISC_FALSE);

	if (dh1->priv_key != NULL || dh2->priv_key != NULL) {
		if (dh1->priv_key == NULL || dh2->priv_key == NULL)
			return (ISC_FALSE);
		if (BN_cmp(dh1->priv_key, dh2->priv_key) != 0)
			return (ISC_FALSE);
	}
	return (ISC_TRUE);
}
