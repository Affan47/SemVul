Tspi_Key_LoadKey(TSS_HKEY hKey,
		 TSS_HKEY hUnwrappingKey)
{
	TPM_AUTH auth;
	TCPA_DIGEST digest;
	TSS_RESULT result;
	UINT32 keyslot;
	TSS_HCONTEXT tspContext;
	TSS_HPOLICY hPolicy;
	UINT32 keySize;
	BYTE *keyBlob;
	TCS_KEY_HANDLE tcsKey, tcsParentHandle;
	TSS_BOOL usesAuth;
	TPM_AUTH *pAuth;
	Trspi_HashCtx hashCtx;
	TPM_COMMAND_CODE ordinal;

	if (!obj_is_rsakey(hUnwrappingKey))
		return TSPERR(TSS_E_INVALID_HANDLE);

	if ((result = obj_rsakey_get_tsp_context(hKey, &tspContext)))
		return result;

	if ((result = obj_context_get_loadkey_ordinal(tspContext, &ordinal)))
		return result;

	if ((result = obj_rsakey_get_blob(hKey, &keySize, &keyBlob)))
		return result;

	if ((result = obj_rsakey_get_tcs_handle(hUnwrappingKey, &tcsParentHandle)))
		return result;

	if ((result = obj_rsakey_get_policy(hUnwrappingKey, TSS_POLICY_USAGE, &hPolicy,
					    &usesAuth))) {
		free_tspi(tspContext, keyBlob);
		return result;
	}

	if (usesAuth) {
		result = Trspi_HashInit(&hashCtx, TSS_HASH_SHA1);
		result |= Trspi_Hash_UINT32(&hashCtx, ordinal);
		result |= Trspi_HashUpdate(&hashCtx, keySize, keyBlob);
		if ((result |= Trspi_HashFinal(&hashCtx, digest.digest))) {
			free_tspi(tspContext, keyBlob);
			return result;
		}

		if ((result = secret_PerformAuth_OIAP(hUnwrappingKey, ordinal, hPolicy, FALSE,
						      &digest, &auth))) {
			free_tspi(tspContext, keyBlob);
			return result;
		}
		pAuth = &auth;
	} else {
		pAuth = NULL;
	}

	if ((result = TCS_API(tspContext)->LoadKeyByBlob(tspContext, tcsParentHandle, keySize,
							 keyBlob, pAuth, &tcsKey, &keyslot))) {
		free_tspi(tspContext, keyBlob);
		return result;
	}

	free_tspi(tspContext, keyBlob);

	if (usesAuth) {
		result = Trspi_HashInit(&hashCtx, TSS_HASH_SHA1);
		result |= Trspi_Hash_UINT32(&hashCtx, result);
		result |= Trspi_Hash_UINT32(&hashCtx, ordinal);
		if (ordinal == TPM_ORD_LoadKey)
			result |= Trspi_Hash_UINT32(&hashCtx, keyslot);
		if ((result |= Trspi_HashFinal(&hashCtx, digest.digest)))
			return result;

		if ((result = obj_policy_validate_auth_oiap(hPolicy, &digest, &auth)))
			return result;
	}

	return obj_rsakey_set_tcs_handle(hKey, tcsKey);
}
