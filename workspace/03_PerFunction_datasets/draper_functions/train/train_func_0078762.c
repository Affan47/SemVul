__tspi_rsa_verify(TSS_HKEY key,
	   UINT32   type,
	   UINT32   hashLen,
	   BYTE*    hash,
	   UINT32   sigLen,
	   BYTE*    sig)
{
	BYTE *blob;
	UINT32 blobLen;
	UINT64 offset;
	TSS_RESULT result;
	TSS_HCONTEXT tspContext;
	TPM_PUBKEY pubKey;

	if (!hash || !sig)
		return TSPERR(TSS_E_INTERNAL_ERROR);

	if ((result = obj_rsakey_get_tsp_context(key, &tspContext)))
		return result;

	if ((result = obj_rsakey_get_pub_blob(key, &blobLen, &blob)))
		return result;

	offset = 0;
	if ((result = Trspi_UnloadBlob_PUBKEY(&offset, blob, &pubKey))) {
		free_tspi(tspContext, blob);
		return result;
	}
	free_tspi(tspContext, blob);

	result = Trspi_Verify(type, hash, hashLen, pubKey.pubKey.key, pubKey.pubKey.keyLength,
			      sig, sigLen);

	free(pubKey.pubKey.key);
	free(pubKey.algorithmParms.parms);

	return result;
}
