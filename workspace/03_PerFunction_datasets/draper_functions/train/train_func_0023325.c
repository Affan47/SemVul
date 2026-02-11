Tspi_Key_GetPubKey(TSS_HKEY hKey,
		   UINT32 * pulPubKeyLength,
		   BYTE ** prgbPubKey)
{
	TPM_AUTH auth;
	TPM_AUTH *pAuth;
	TCPA_DIGEST digest;
	TCPA_RESULT result;
	TSS_HCONTEXT tspContext;
	TSS_HPOLICY hPolicy;
	TCS_KEY_HANDLE tcsKeyHandle;
	TSS_BOOL usesAuth;
	Trspi_HashCtx hashCtx;

	if (pulPubKeyLength == NULL || prgbPubKey == NULL)
		return TSPERR(TSS_E_BAD_PARAMETER);

	if ((result = obj_rsakey_get_tsp_context(hKey, &tspContext)))
		return result;

	if ((result = obj_rsakey_get_policy(hKey, TSS_POLICY_USAGE,
					    &hPolicy, &usesAuth)))
		return result;

	if ((result = obj_rsakey_get_tcs_handle(hKey, &tcsKeyHandle)))
		return result;

	if (usesAuth) {
		result = Trspi_HashInit(&hashCtx, TSS_HASH_SHA1);
		result |= Trspi_Hash_UINT32(&hashCtx, TPM_ORD_GetPubKey);
		if ((result |= Trspi_HashFinal(&hashCtx, digest.digest)))
			return result;

		if ((result = secret_PerformAuth_OIAP(hKey, TPM_ORD_GetPubKey, hPolicy, FALSE,
						      &digest, &auth)))
			return result;
		pAuth = &auth;
	} else {
		pAuth = NULL;
	}

	if ((result = TCS_API(tspContext)->GetPubKey(tspContext, tcsKeyHandle, pAuth,
						     pulPubKeyLength, prgbPubKey)))
		return result;

	if (usesAuth) {
		result = Trspi_HashInit(&hashCtx, TSS_HASH_SHA1);
		result |= Trspi_Hash_UINT32(&hashCtx, result);
		result |= Trspi_Hash_UINT32(&hashCtx, TPM_ORD_GetPubKey);
		result |= Trspi_HashUpdate(&hashCtx, *pulPubKeyLength, *prgbPubKey);
		if ((result |= Trspi_HashFinal(&hashCtx, digest.digest)))
			goto error;


		if ((result = obj_policy_validate_auth_oiap(hPolicy, &digest, &auth)))
			goto error;
	}

	if ((result = __tspi_add_mem_entry(tspContext, *prgbPubKey)))
		goto error;

	if (tcsKeyHandle == TPM_KEYHND_SRK)
		obj_rsakey_set_pubkey(hKey, TRUE, *prgbPubKey);

	return TSS_SUCCESS;
error:
	free(*prgbPubKey);
	*prgbPubKey = NULL;
	*pulPubKeyLength = 0;
	return result;
}
