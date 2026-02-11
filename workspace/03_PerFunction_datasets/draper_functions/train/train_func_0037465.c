generate_session_key(const char *filename, const char *keynamestr,
		     dns_name_t *keyname, const char *algstr,
		     dns_name_t *algname, unsigned int algtype,
		     isc_uint16_t bits, isc_mem_t *mctx,
		     dns_tsigkey_t **tsigkeyp)
{
	isc_result_t result = ISC_R_SUCCESS;
	dst_key_t *key = NULL;
	isc_buffer_t key_txtbuffer;
	isc_buffer_t key_rawbuffer;
	char key_txtsecret[256];
	char key_rawsecret[64];
	isc_region_t key_rawregion;
	isc_stdtime_t now;
	dns_tsigkey_t *tsigkey = NULL;
	FILE *fp = NULL;

	isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
		      NS_LOGMODULE_SERVER, ISC_LOG_INFO,
		      "generating session key for dynamic DNS");


	result = dst_key_generate(keyname, algtype, bits, 1, 0,
				  DNS_KEYPROTO_ANY, dns_rdataclass_in,
				  mctx, &key);
	if (result != ISC_R_SUCCESS)
		return (result);


	isc_buffer_init(&key_rawbuffer, &key_rawsecret, sizeof(key_rawsecret));
	CHECK(dst_key_tobuffer(key, &key_rawbuffer));

	isc_buffer_usedregion(&key_rawbuffer, &key_rawregion);
	isc_buffer_init(&key_txtbuffer, &key_txtsecret, sizeof(key_txtsecret));
	CHECK(isc_base64_totext(&key_rawregion, -1, "", &key_txtbuffer));


	isc_stdtime_get(&now);
	CHECK(dns_tsigkey_createfromkey(dst_key_name(key), algname, key,
					ISC_FALSE, NULL, now, now, mctx, NULL,
					&tsigkey));


	fp = ns_os_openfile(filename, S_IRUSR|S_IWUSR, ISC_TRUE);
	if (fp == NULL) {
		isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
			      NS_LOGMODULE_SERVER, ISC_LOG_ERROR,
			      "could not create %s", filename);
		result = ISC_R_NOPERM;
		goto cleanup;
	}

	fprintf(fp, "key \"%s\" {\n"
		"\talgorithm %s;\n"
		"\tsecret \"%.*s\";\n};\n", keynamestr, algstr,
		(int) isc_buffer_usedlength(&key_txtbuffer),
		(char*) isc_buffer_base(&key_txtbuffer));

	RUNTIME_CHECK(isc_stdio_flush(fp) == ISC_R_SUCCESS);
	RUNTIME_CHECK(isc_stdio_close(fp) == ISC_R_SUCCESS);

	dst_key_free(&key);

	*tsigkeyp = tsigkey;

	return (ISC_R_SUCCESS);

  cleanup:
	isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
		      NS_LOGMODULE_SERVER, ISC_LOG_ERROR,
		      "failed to generate session key "
		      "for dynamic DNS: %s", isc_result_totext(result));
	if (tsigkey != NULL)
		dns_tsigkey_detach(&tsigkey);
	if (key != NULL)
		dst_key_free(&key);

	return (result);
}
