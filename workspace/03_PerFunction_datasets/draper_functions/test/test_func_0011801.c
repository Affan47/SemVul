sealx_mask_cb(PVOID lpAppData,
	      TSS_HKEY hEncKey,
	      TSS_HENCDATA hEncData,
	      TSS_ALGORITHM_ID algId,
	      UINT32 ulSizeNonces,
	      BYTE *rgbNonceEven,
	      BYTE *rgbNonceOdd,
	      BYTE *rgbNonceEvenOSAP,
	      BYTE *rgbNonceOddOSAP,
	      UINT32 ulDataLength,
	      BYTE *rgbDataToMask,
	      BYTE *rgbMaskedData)
{
	UINT32 mgf1SeedLen, sharedSecretLen = sizeof(TPM_DIGEST);
	BYTE *mgf1Seed, *mgf1Buffer;
	UINT32 i;
	TSS_RESULT result;
	struct authsess *sess = (struct authsess *)lpAppData;

	mgf1SeedLen = (ulSizeNonces * 2) + strlen("XOR") + sharedSecretLen;
	if ((mgf1Seed = (BYTE *)calloc(1, mgf1SeedLen)) == NULL) {
		LogError("malloc of %u bytes failed.", mgf1SeedLen);
		return TSPERR(TSS_E_OUTOFMEMORY);
	}
	mgf1Buffer = mgf1Seed;
	memcpy(mgf1Buffer, rgbNonceEven, ulSizeNonces);
	mgf1Buffer += ulSizeNonces;
	memcpy(mgf1Buffer, rgbNonceOdd, ulSizeNonces);
	mgf1Buffer += ulSizeNonces;
	memcpy(mgf1Buffer, "XOR", strlen("XOR"));
	mgf1Buffer += strlen("XOR");
	memcpy(mgf1Buffer, sess->sharedSecret.digest, sharedSecretLen);

	if ((result = Trspi_MGF1(TSS_HASH_SHA1, mgf1SeedLen, mgf1Seed, ulDataLength,
				 rgbMaskedData)))
		goto done;

	for (i = 0; i < ulDataLength; i++)
		rgbMaskedData[i] ^= rgbDataToMask[i];

done:
	free(mgf1Seed);

	return result;
}
