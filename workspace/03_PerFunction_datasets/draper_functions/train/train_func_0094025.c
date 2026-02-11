obj_rsakey_get_modulus(TSS_HKEY hKey, UINT32 *size, BYTE **data)
{
	struct tsp_object *obj;
	struct tr_rsakey_obj *rsakey;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&rsakey_list, hKey)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	rsakey = (struct tr_rsakey_obj *)obj->data;


	if (rsakey->tcsHandle == TPM_KEYHND_SRK) {
		BYTE zeroBlob[2048] = { 0, };

		if (!memcmp(rsakey->key.pubKey.key, zeroBlob, rsakey->key.pubKey.keyLength)) {
			result = TSPERR(TSS_E_BAD_PARAMETER);
			goto done;
		}
	}

	*data = calloc_tspi(obj->tspContext, rsakey->key.pubKey.keyLength);
	if (*data == NULL) {
		LogError("malloc of %u bytes failed.", rsakey->key.pubKey.keyLength);
		result = TSPERR(TSS_E_OUTOFMEMORY);
		goto done;
	}
	*size = rsakey->key.pubKey.keyLength;
	memcpy(*data, rsakey->key.pubKey.key, rsakey->key.pubKey.keyLength);

done:
	obj_list_put(&rsakey_list);

	return result;
}
