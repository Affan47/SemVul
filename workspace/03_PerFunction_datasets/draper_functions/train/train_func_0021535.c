obj_nvstore_create_pcrshortinfo(TSS_HNVSTORE hNvstore,
				TSS_HPCRS hPcrComposite,
				UINT32 *size,
				BYTE **data)
{
	struct tsp_object *obj;
	BYTE pdata[MAX_PUBLIC_DATA_SIZE];
	UINT32 dataLen;
	UINT64 offset;
	TSS_HCONTEXT tspContext;
	TSS_RESULT result = TSS_SUCCESS;
	BYTE*  ppbHashData;
	UINT32 i;
	BYTE  digAtRelease[TPM_SHA1_160_HASH_LEN] = { 0, };
	UINT32 tmp_locAtRelease;
	TPM_LOCALITY_SELECTION locAtRelease = TPM_LOC_ZERO | TPM_LOC_ONE
					| TPM_LOC_TWO | TPM_LOC_THREE| TPM_LOC_FOUR;
	BYTE tmp_pcr_select[3] = {0, 0, 0};
	TCPA_PCR_SELECTION pcrSelect = { 3, tmp_pcr_select};

	if ((obj = obj_list_get_obj(&nvstore_list, hNvstore)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	tspContext = obj->tspContext;

	if (hPcrComposite) {
		if ((result = obj_pcrs_get_selection(hPcrComposite, &dataLen, pdata))) {
			LogDebug("get_selection error from hReadPcrComposite");
			goto out;
		}


		if (dataLen - sizeof(UINT16) > 3) {
			result = TSPERR(TSS_E_BAD_PARAMETER);
			goto out;
		}
		offset = 0;
		Trspi_UnloadBlob_PCR_SELECTION(&offset, pdata, &pcrSelect);

		if (pcrSelect.sizeOfSelect != 0) {
			if ((result = obj_pcrs_get_digest_at_release(hPcrComposite,
								     &dataLen, &ppbHashData))) {
				LogDebug("get_composite error from hReadPcrComposite");
				goto out;
			}
			memcpy(digAtRelease, ppbHashData, dataLen);
			free_tspi(tspContext, ppbHashData);
		} else {
			pcrSelect.sizeOfSelect = 3;
			pcrSelect.pcrSelect = tmp_pcr_select;
		}

		if (pcrSelect.sizeOfSelect < 3) {
			for (i = 0; i < pcrSelect.sizeOfSelect; i++) {
				tmp_pcr_select[i] = pcrSelect.pcrSelect[i];
			}
			pcrSelect.sizeOfSelect = 3;
			pcrSelect.pcrSelect = tmp_pcr_select;
		}

		if ((result = obj_pcrs_get_locality(hPcrComposite, &tmp_locAtRelease)))
			goto out;
		locAtRelease = (TPM_LOCALITY_SELECTION)(tmp_locAtRelease & TSS_LOCALITY_MASK);
	}

	*size = sizeof(UINT16) + 3 + sizeof(TPM_LOCALITY_SELECTION) + TPM_SHA1_160_HASH_LEN;
	*data = calloc_tspi(tspContext, *size);
	if (*data == NULL) {
		LogError("malloc of %u bytes failed.", *size);
		result = TSPERR(TSS_E_OUTOFMEMORY);
		goto out;
	}

	offset = 0;
	Trspi_LoadBlob_PCR_SELECTION(&offset, *data, &pcrSelect);
	Trspi_LoadBlob_BYTE(&offset, locAtRelease, *data);
	Trspi_LoadBlob(&offset, TPM_SHA1_160_HASH_LEN, *data, digAtRelease);

out:
	obj_list_put(&nvstore_list);
	return result;
}
