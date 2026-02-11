Transport_EvictKey(TSS_HCONTEXT tspContext,
		   TCS_KEY_HANDLE hKey)
{
	TSS_RESULT result;
	UINT32 handlesLen;
	TCS_HANDLE *handles, handle;
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

	result = obj_context_transport_execute(tspContext, TPM_ORD_EvictKey, 0, NULL, &pubKeyHash,
					       &handlesLen, &handles, NULL, NULL, NULL, NULL);

	return result;
}
