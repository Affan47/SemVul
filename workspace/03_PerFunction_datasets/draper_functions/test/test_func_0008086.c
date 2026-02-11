Trspi_LoadBlob_MSA_COMPOSITE(UINT64 *offset, BYTE *blob, TPM_MSA_COMPOSITE *msaComp)
{
	UINT32 i;

	Trspi_LoadBlob_UINT32(offset, msaComp->MSAlist, blob);
	for (i = 0; i < msaComp->MSAlist; i++)
		Trspi_LoadBlob_DIGEST(offset, blob, &msaComp->migAuthDigest[i]);
}
