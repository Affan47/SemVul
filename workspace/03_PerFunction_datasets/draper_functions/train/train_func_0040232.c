fill_key_info(struct key_disk_cache *d, struct key_mem_cache *m, TSS_KM_KEYINFO *key_info)
{
	BYTE tmp_blob[2048];
	UINT16 tmp_blob_size = 2048;
	TSS_KEY tmp_key;
	UINT64 offset;
	TSS_RESULT result;

	if (m == NULL) {
		key_info->fIsLoaded = FALSE;


		if ((result = ps_get_key_by_cache_entry(d, (BYTE *)&tmp_blob, &tmp_blob_size)))
			return result;

		offset = 0;

		if ((result = UnloadBlob_TSS_KEY(&offset, tmp_blob, &tmp_key)))
			return result;

		if (tmp_key.hdr.key12.tag == TPM_TAG_KEY12) {
			key_info->versionInfo.bMajor = TSS_SPEC_MAJOR;
			key_info->versionInfo.bMinor = TSS_SPEC_MINOR;
			key_info->versionInfo.bRevMajor = 0;
			key_info->versionInfo.bRevMajor = 0;
		} else
			memcpy(&key_info->versionInfo, &tmp_key.hdr.key11.ver, sizeof(TSS_VERSION));
		memcpy(&key_info->bAuthDataUsage, &tmp_key.authDataUsage,
		       sizeof(TCPA_AUTH_DATA_USAGE));
		destroy_key_refs(&tmp_key);
	} else {
		if (m->tpm_handle == NULL_TPM_HANDLE)
			key_info->fIsLoaded = FALSE;
		else
			key_info->fIsLoaded = TRUE;

		if (m->blob->hdr.key12.tag == TPM_TAG_KEY12) {
			key_info->versionInfo.bMajor = TSS_SPEC_MAJOR;
			key_info->versionInfo.bMinor = TSS_SPEC_MINOR;
			key_info->versionInfo.bRevMajor = 0;
			key_info->versionInfo.bRevMajor = 0;
		} else
			memcpy(&key_info->versionInfo, &m->blob->hdr.key11.ver, sizeof(TSS_VERSION));
		memcpy(&key_info->bAuthDataUsage, &m->blob->authDataUsage,
		       sizeof(TCPA_AUTH_DATA_USAGE));
	}

	memcpy(&key_info->keyUUID, &d->uuid, sizeof(TSS_UUID));
	memcpy(&key_info->parentKeyUUID, &d->parent_uuid, sizeof(TSS_UUID));

	return get_vendor_data(d, &key_info->ulVendorDataLength, &key_info->rgbVendorData);
}
