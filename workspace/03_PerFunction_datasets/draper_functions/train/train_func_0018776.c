hmacsha384_parse(dst_key_t *key, isc_lex_t *lexer, dst_key_t *pub) {
	dst_private_t priv;
	isc_result_t result, tresult;
	isc_buffer_t b;
	isc_mem_t *mctx = key->mctx;
	unsigned int i;

	UNUSED(pub);

	result = dst__privstruct_parse(key, DST_ALG_HMACSHA384, lexer, mctx,
				       &priv);
	if (result != ISC_R_SUCCESS)
		return (result);

	key->key_bits = 0;
	for (i = 0; i < priv.nelements; i++) {
		switch (priv.elements[i].tag) {
		case TAG_HMACSHA384_KEY:
			isc_buffer_init(&b, priv.elements[i].data,
					priv.elements[i].length);
			isc_buffer_add(&b, priv.elements[i].length);
			tresult = hmacsha384_fromdns(key, &b);
			if (tresult != ISC_R_SUCCESS)
				result = tresult;
			break;
		case TAG_HMACSHA384_BITS:
			tresult = getkeybits(key, &priv.elements[i]);
			if (tresult != ISC_R_SUCCESS)
				result = tresult;
			break;
		default:
			result = DST_R_INVALIDPRIVATEKEY;
			break;
		}
	}
	dst__privstruct_free(&priv, mctx);
	memset(&priv, 0, sizeof(priv));
	return (result);
}
