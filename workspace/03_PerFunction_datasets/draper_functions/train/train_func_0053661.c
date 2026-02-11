tds_answer_challenge_ntlmv2(TDSSOCKET * tds,
		     TDSCONNECTION * connection,
		     const unsigned char *challenge,
		     TDS_UINT * flags,
		     const unsigned char *names_blob, TDS_INT names_blob_len, TDSANSWER * answer, unsigned char **ntlm_v2_response)
{
	int res;
	const char *passwd = tds_dstr_cstr(&connection->password);


	unsigned char *lm_v2_response;
	unsigned char ntlm_v2_hash[16];
	const names_blob_prefix_t *names_blob_prefix;

	res = make_ntlm_v2_hash(tds, passwd, ntlm_v2_hash);
	if (res != TDS_SUCCEED)
		return res;


	names_blob_prefix = (const names_blob_prefix_t *) names_blob;
	lm_v2_response = make_lm_v2_response(ntlm_v2_hash, names_blob_prefix->challenge, 8, challenge);
	if (!lm_v2_response)
		return TDS_FAIL;
	memcpy(answer->lm_resp, lm_v2_response, 24);
	free(lm_v2_response);


	*ntlm_v2_response = make_lm_v2_response(ntlm_v2_hash, names_blob, names_blob_len, challenge);
	if (!*ntlm_v2_response)
		return TDS_FAIL;

	memset(ntlm_v2_hash, 0, sizeof(ntlm_v2_hash));


	*flags &= ~0x4000;
	return TDS_SUCCEED;
}
