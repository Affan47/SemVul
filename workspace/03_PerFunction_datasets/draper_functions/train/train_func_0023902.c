obj_nvstore_get_state_readstclear(TSS_HNVSTORE hNvstore, UINT32 * readstclear)
{
	BYTE nv_data_public[MAX_PUBLIC_DATA_SIZE];
	UINT32 data_public_size = MAX_PUBLIC_DATA_SIZE;
	UINT32 offset;
	UINT16 pcrread_sizeOfSelect;
	UINT16 pcrwrite_sizeOfSelect;
	TPM_BOOL value;
	TSS_RESULT result;

	if ((result = obj_nvstore_get_datapublic(hNvstore, &data_public_size, nv_data_public)))
		return result;

	offset = sizeof(TPM_STRUCTURE_TAG)+ sizeof(TPM_NV_INDEX);
	pcrread_sizeOfSelect = Decode_UINT16(nv_data_public + offset);
	offset = offset + sizeof(UINT16) + pcrread_sizeOfSelect
			+ sizeof(TPM_LOCALITY_SELECTION)
			+ sizeof(TPM_COMPOSITE_HASH);

	pcrwrite_sizeOfSelect = Decode_UINT16(nv_data_public + offset);
	offset = offset + sizeof(UINT16) + pcrwrite_sizeOfSelect
			+ sizeof(TPM_LOCALITY_SELECTION)
			+ sizeof(TPM_COMPOSITE_HASH)
			+ sizeof(TPM_NV_ATTRIBUTES);

	value = *((TPM_BOOL *)(nv_data_public + offset));

	*readstclear = value;

	return result;
}
