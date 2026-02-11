obj_pcrs_set_digest_at_release(TSS_HPCRS hPcrs, TPM_COMPOSITE_HASH digest)
{
	struct tsp_object *obj;
	struct tr_pcrs_obj *pcrs;
	TSS_RESULT result = TSS_SUCCESS;
	TPM_COMPOSITE_HASH *dig;

	LogDebugFn("######## Digest to be set on TSS object:");
	LogDebugData(TCPA_SHA1_160_HASH_LEN, digest.digest);

	if ((obj = obj_list_get_obj(&pcrs_list, hPcrs)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	pcrs = (struct tr_pcrs_obj *)obj->data;

	switch(pcrs->type) {
	case TSS_PCRS_STRUCT_INFO:
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);
		goto done;
	case TSS_PCRS_STRUCT_INFO_SHORT:
		dig = &pcrs->info.infoshort.digestAtRelease;
		break;
	case TSS_PCRS_STRUCT_INFO_LONG:
		dig = &pcrs->info.infolong.digestAtRelease;
		break;
	default:
		LogDebugFn("Undefined type of PCRs object");
		result = TSPERR(TSS_E_INTERNAL_ERROR);
		goto done;
	}


	memcpy(dig->digest,&digest.digest,TPM_SHA1_160_HASH_LEN);

	LogDebugFn("######## Digest SET on TSS object:");
	LogDebugData(TCPA_SHA1_160_HASH_LEN,pcrs->info.infoshort.digestAtRelease.digest);

done:
	obj_list_put(&pcrs_list);

	return result;
}
