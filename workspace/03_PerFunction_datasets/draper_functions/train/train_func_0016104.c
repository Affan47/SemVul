obj_migdata_set_msa_pubkey(TSS_HMIGDATA hMigData, UINT32 blobSize, BYTE *pubKeyBlob)
{
	struct tsp_object *obj;
	struct tr_migdata_obj *migdata;
	UINT32 size;
	TPM_DIGEST msaDigest;
	TPM_DIGEST *digest;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&migdata_list, hMigData)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	migdata = (struct tr_migdata_obj *)obj->data;

	if ((result = obj_migdata_calc_pubkey_digest(blobSize, pubKeyBlob, &msaDigest)))
		goto done;

	size = (migdata->msaList.MSAlist + 1) * sizeof(*digest);
	if ((migdata->msaList.migAuthDigest = realloc(migdata->msaList.migAuthDigest, size)) == NULL) {
		LogError("malloc of %u bytes failed.", size);
		result = TSPERR(TSS_E_OUTOFMEMORY);
		goto done;
	}
	digest = migdata->msaList.migAuthDigest + migdata->msaList.MSAlist;
	*digest = msaDigest;
	migdata->msaList.MSAlist++;

	result = obj_migdata_calc_msa_digest(migdata);

done:
	obj_list_put(&migdata_list);

	return result;
}
