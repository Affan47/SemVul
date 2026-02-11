Transport_GetAuditDigestSigned(TSS_HCONTEXT tspContext,
			       TCS_KEY_HANDLE keyHandle,
			       TSS_BOOL closeAudit,
			       TPM_NONCE *antiReplay,
			       TPM_AUTH *privAuth,
			       UINT32 *counterValueSize,
			       BYTE **counterValue,
			       TPM_DIGEST *auditDigest,
			       TPM_DIGEST *ordinalDigest,
			       UINT32 *sigSize,
			       BYTE **sig)
{
        TSS_RESULT result;
        UINT32 handlesLen, decLen;
        TCS_HANDLE *handles, handle;
        BYTE *dec = NULL;
        TPM_DIGEST pubKeyHash;
        Trspi_HashCtx hashCtx;
        UINT64 offset;
        BYTE data[sizeof(TSS_BOOL) + sizeof(TPM_NONCE)];


	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	if ((result = obj_tcskey_get_pubkeyhash(keyHandle, pubKeyHash.digest)))
		return result;

	result = Trspi_HashInit(&hashCtx, TSS_HASH_SHA1);
	result |= Trspi_Hash_DIGEST(&hashCtx, pubKeyHash.digest);
	if ((result |= Trspi_HashFinal(&hashCtx, pubKeyHash.digest)))
		return result;

	handlesLen = 1;
	handle = keyHandle;
	handles = &handle;

	offset = 0;
	Trspi_LoadBlob_BOOL(&offset, closeAudit, data);
	Trspi_LoadBlob_NONCE(&offset, data, antiReplay);

	if ((result = obj_context_transport_execute(tspContext, TPM_ORD_GetAuditDigestSigned,
						    sizeof(data), data, &pubKeyHash, &handlesLen,
						    &handles, privAuth, NULL, &decLen, &dec)))
		return result;

	offset = 0;
	Trspi_UnloadBlob_COUNTER_VALUE(&offset, dec, NULL);

	*counterValueSize = (UINT32)offset;
	if ((*counterValue = malloc(*counterValueSize)) == NULL) {
		free(dec);
		LogError("malloc of %u bytes failed", *counterValueSize);
		*counterValueSize = 0;
		return TSPERR(TSS_E_OUTOFMEMORY);
	}
	offset = 0;
	Trspi_UnloadBlob(&offset, *counterValueSize, dec, *counterValue);

	Trspi_UnloadBlob_DIGEST(&offset, dec, auditDigest);
	Trspi_UnloadBlob_DIGEST(&offset, dec, ordinalDigest);

	Trspi_UnloadBlob_UINT32(&offset, sigSize, dec);

	if ((*sig = malloc(*sigSize)) == NULL) {
		free(dec);
		free(*counterValue);
		*counterValue = NULL;
		*counterValueSize = 0;
		LogError("malloc of %u bytes failed", *sigSize);
		*counterValueSize = 0;
		return TSPERR(TSS_E_OUTOFMEMORY);
	}
	Trspi_UnloadBlob(&offset, *sigSize, dec, *sig);

	return TSS_SUCCESS;
}
