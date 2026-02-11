setup_tsec(char *keyfile, isc_mem_t *mctx) {
	dst_key_t *dstkey = NULL;
	isc_result_t result;
	dns_tsectype_t tsectype;

	result = dst_key_fromnamedfile(keyfile, NULL,
				       DST_TYPE_PRIVATE | DST_TYPE_KEY, mctx,
				       &dstkey);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "could not read key from %s: %s\n",
			keyfile, isc_result_totext(result));
		exit(1);
	}

	if (dst_key_alg(dstkey) == DST_ALG_HMACMD5)
		tsectype = dns_tsectype_tsig;
	else
		tsectype = dns_tsectype_sig0;

	result = dns_tsec_create(mctx, tsectype, dstkey, &tsec);
	dst_key_free(&dstkey);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "could not create tsec: %s\n",
			isc_result_totext(result));
		exit(1);
	}
}
