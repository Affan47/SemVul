Transport_GetPubKey(TSS_HCONTEXT tspContext,
		    TCS_KEY_HANDLE hKey,
		    TPM_AUTH *pAuth,
		    UINT32 *pcPubKeySize,
		    BYTE **prgbPubKey)
{
	TSS_RESULT result;
	UINT32 handlesLen, decLen;
	TCS_HANDLE *handles, handle;
	BYTE *dec = NULL;
	TPM_DIGEST pubKeyHash;
	Trspi_HashCtx hashCtx;


	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	if ((result = obj_tcskey_get_pubkeyhash(hKey, pubKeyHash.digest)))
		return result;

	result = Trspi_HashInit(&hashCtx, TSS_HASH_SHA1);
	result |= Trspi_Hash_DIGEST(&hashCtx, pubKeyHash.digest);
	if ((result |= Trspi_HashFinal(&hashCtx, pubKeyHash.digest)))
		return result;

	handlesLen = 1;
	handle = hKey;
	handles = &handle;

	if ((result = obj_context_transport_execute(tspContext, TPM_ORD_GetPubKey, 0, NULL,
						    &pubKeyHash, &handlesLen, &handles, pAuth, NULL,
						    &decLen, &dec)))
		return result;

	*prgbPubKey = dec;
	*pcPubKeySize = decLen;

	return result;
}
