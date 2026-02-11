obj_encdata_get_pcr_selection(TSS_HENCDATA hEncData,
			      TSS_FLAG pcrInfoType,
			      TSS_FLAG dir,
			      UINT32 *size,
			      BYTE **data)
{
	struct tsp_object *obj;
	struct tr_encdata_obj *encdata;
	TSS_RESULT result = TSS_SUCCESS;
	TPM_PCR_SELECTION *selection = NULL;
	UINT64 offset;

	if ((obj = obj_list_get_obj(&encdata_list, hEncData)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	encdata = (struct tr_encdata_obj *)obj->data;

	if (pcrInfoType != encdata->pcrInfoType) {
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);
		goto done;
	}

	switch (pcrInfoType) {
		case TSS_PCRS_STRUCT_INFO:
			if (dir == TSS_TSPATTRIB_ENCDATAPCR_SELECTION)
				selection = &encdata->pcrInfo.info11.pcrSelection;
			break;
		case TSS_PCRS_STRUCT_INFO_LONG:
			if (dir == TSS_TSPATTRIB_ENCDATAPCRLONG_CREATION_SELECTION)
				selection = &encdata->pcrInfo.infolong.creationPCRSelection;
			else if (dir == TSS_TSPATTRIB_ENCDATAPCRLONG_RELEASE_SELECTION)
				selection = &encdata->pcrInfo.infolong.releasePCRSelection;
			else {
				result = TSPERR(TSS_E_INTERNAL_ERROR);
				goto done;
			}
			break;
		default:
			result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);
			goto done;
	}

	if (selection == NULL) {
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);
		goto done;
	}

	*size = sizeof(UINT16) + selection->sizeOfSelect;

	if ((*data = calloc_tspi(obj->tspContext, *size)) == NULL) {
		LogError("malloc of %u bytes failed.", *size);
		*size = 0;
		result = TSPERR(TSS_E_OUTOFMEMORY);
		goto done;
	}

	offset = 0;
	Trspi_LoadBlob_PCR_SELECTION(&offset, *data, selection);
done:
	obj_list_put(&encdata_list);

	return result;
}
