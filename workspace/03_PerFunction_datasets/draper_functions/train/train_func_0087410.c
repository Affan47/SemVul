setup_file_key(void) {
	isc_result_t result;
	dst_key_t *dstkey = NULL;

	debug("setup_file_key()");


	result = dst_key_fromnamedfile(keyfile, NULL,
				       DST_TYPE_PRIVATE | DST_TYPE_KEY, mctx,
				       &dstkey);


	if (result != ISC_R_SUCCESS) {
		result = read_confkey();
		if (result == ISC_R_SUCCESS)
			return;
	}

	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "Couldn't read key from %s: %s\n",
			keyfile, isc_result_totext(result));
		goto failure;
	}

	switch (dst_key_alg(dstkey)) {
	case DST_ALG_HMACMD5:
		hmacname = DNS_TSIG_HMACMD5_NAME;
		break;
	case DST_ALG_HMACSHA1:
		hmacname = DNS_TSIG_HMACSHA1_NAME;
		break;
	case DST_ALG_HMACSHA224:
		hmacname = DNS_TSIG_HMACSHA224_NAME;
		break;
	case DST_ALG_HMACSHA256:
		hmacname = DNS_TSIG_HMACSHA256_NAME;
		break;
	case DST_ALG_HMACSHA384:
		hmacname = DNS_TSIG_HMACSHA384_NAME;
		break;
	case DST_ALG_HMACSHA512:
		hmacname = DNS_TSIG_HMACSHA512_NAME;
		break;
	default:
		printf(";; Couldn't create key %s: bad algorithm\n",
		       keynametext);
		goto failure;
	}
	result = dns_tsigkey_createfromkey(dst_key_name(dstkey), hmacname,
					   dstkey, ISC_FALSE, NULL, 0, 0,
					   mctx, NULL, &key);
	if (result != ISC_R_SUCCESS) {
		printf(";; Couldn't create key %s: %s\n",
		       keynametext, isc_result_totext(result));
		goto failure;
	}
 failure:
	if (dstkey != NULL)
		dst_key_free(&dstkey);
}
