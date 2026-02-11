openssldsa_tofile(const dst_key_t *key, const char *directory) {
	int cnt = 0;
	DSA *dsa;
	dst_private_t priv;
	unsigned char bufs[5][128];

	if (key->keydata.dsa == NULL)
		return (DST_R_NULLKEY);

	if (key->external) {
		priv.nelements = 0;
		return (dst__privstruct_writefile(key, &priv, directory));
	}

	dsa = key->keydata.dsa;

	priv.elements[cnt].tag = TAG_DSA_PRIME;
	priv.elements[cnt].length = BN_num_bytes(dsa->p);
	BN_bn2bin(dsa->p, bufs[cnt]);
	priv.elements[cnt].data = bufs[cnt];
	cnt++;

	priv.elements[cnt].tag = TAG_DSA_SUBPRIME;
	priv.elements[cnt].length = BN_num_bytes(dsa->q);
	BN_bn2bin(dsa->q, bufs[cnt]);
	priv.elements[cnt].data = bufs[cnt];
	cnt++;

	priv.elements[cnt].tag = TAG_DSA_BASE;
	priv.elements[cnt].length = BN_num_bytes(dsa->g);
	BN_bn2bin(dsa->g, bufs[cnt]);
	priv.elements[cnt].data = bufs[cnt];
	cnt++;

	priv.elements[cnt].tag = TAG_DSA_PRIVATE;
	priv.elements[cnt].length = BN_num_bytes(dsa->priv_key);
	BN_bn2bin(dsa->priv_key, bufs[cnt]);
	priv.elements[cnt].data = bufs[cnt];
	cnt++;

	priv.elements[cnt].tag = TAG_DSA_PUBLIC;
	priv.elements[cnt].length = BN_num_bytes(dsa->pub_key);
	BN_bn2bin(dsa->pub_key, bufs[cnt]);
	priv.elements[cnt].data = bufs[cnt];
	cnt++;

	priv.nelements = cnt;
	return (dst__privstruct_writefile(key, &priv, directory));
}
