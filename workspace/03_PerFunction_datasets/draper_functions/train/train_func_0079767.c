setup_keystr(void) {
	unsigned char *secret = NULL;
	int secretlen;
	isc_buffer_t secretbuf;
	isc_result_t result;
	isc_buffer_t keynamesrc;
	char *secretstr;
	char *s, *n;
	dns_fixedname_t fkeyname;
	dns_name_t *keyname;
	char *name;
	dns_name_t *hmacname = NULL;
	isc_uint16_t digestbits = 0;

	dns_fixedname_init(&fkeyname);
	keyname = dns_fixedname_name(&fkeyname);

	debug("Creating key...");

	s = strchr(keystr, ':');
	if (s == NULL || s == keystr || s[1] == 0)
		fatal("key option must specify [hmac:]keyname:secret");
	secretstr = s + 1;
	n = strchr(secretstr, ':');
	if (n != NULL) {
		if (n == secretstr || n[1] == 0)
			fatal("key option must specify [hmac:]keyname:secret");
		name = secretstr;
		secretstr = n + 1;
		digestbits = parse_hmac(&hmacname, keystr, s - keystr);
	} else {
		hmacname = DNS_TSIG_HMACMD5_NAME;
		name = keystr;
		n = s;
	}

	isc_buffer_init(&keynamesrc, name, (unsigned int)(n - name));
	isc_buffer_add(&keynamesrc, (unsigned int)(n - name));

	debug("namefromtext");
	result = dns_name_fromtext(keyname, &keynamesrc, dns_rootname, 0, NULL);
	check_result(result, "dns_name_fromtext");

	secretlen = strlen(secretstr) * 3 / 4;
	secret = isc_mem_allocate(mctx, secretlen);
	if (secret == NULL)
		fatal("out of memory");

	isc_buffer_init(&secretbuf, secret, secretlen);
	result = isc_base64_decodestring(secretstr, &secretbuf);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "could not create key from %s: %s\n",
			keystr, isc_result_totext(result));
		goto failure;
	}

	secretlen = isc_buffer_usedlength(&secretbuf);

	debug("keycreate");
	result = dns_tsigkey_create(keyname, hmacname, secret, secretlen,
				    ISC_FALSE, NULL, 0, 0, mctx, NULL,
				    &tsigkey);
	if (result != ISC_R_SUCCESS)
		fprintf(stderr, "could not create key from %s: %s\n",
			keystr, dns_result_totext(result));
	else
		dst_key_setbits(tsigkey->key, digestbits);
 failure:
	if (secret != NULL)
		isc_mem_free(mctx, secret);
}
