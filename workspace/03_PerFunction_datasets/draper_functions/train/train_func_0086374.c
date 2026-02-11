get_delegate_index(TSS_HCONTEXT hContext, UINT32 index, TPM_DELEGATE_PUBLIC *public)
{
	UINT32 familyTableSize, delegateTableSize;
	BYTE *familyTable = NULL, *delegateTable = NULL;
	UINT64 offset;
	UINT32 tpmIndex;
	TPM_DELEGATE_PUBLIC tempPublic;
	TSS_RESULT result;

	if ((result = TCS_API(hContext)->Delegate_ReadTable(hContext, &familyTableSize,
							    &familyTable, &delegateTableSize,
							    &delegateTable)))
		goto done;

	for (offset = 0; offset < delegateTableSize;) {
		Trspi_UnloadBlob_UINT32(&offset, &tpmIndex, delegateTable);
		if (tpmIndex == index) {
			result = Trspi_UnloadBlob_TPM_DELEGATE_PUBLIC(&offset, delegateTable, public);
			goto done;
		} else {
			if ((result = Trspi_UnloadBlob_TPM_DELEGATE_PUBLIC(&offset, delegateTable, &tempPublic)))
				goto done;
		}

		free(tempPublic.pcrInfo.pcrSelection.pcrSelect);
	}


	result = TSPERR(TSS_E_BAD_PARAMETER);

done:
	free(familyTable);
	free(delegateTable);

	return result;
}
