obj_migdata_add(TSS_HCONTEXT hContext, TSS_HOBJECT *phObject)
{
	TSS_RESULT result;
	struct tr_migdata_obj *migdata = calloc(1, sizeof(struct tr_migdata_obj));

	if (migdata == NULL) {
		LogError("malloc of %zd bytes failed.",	sizeof(struct tr_migdata_obj));
		return TSPERR(TSS_E_OUTOFMEMORY);
	}

	if ((result = obj_list_add(&migdata_list, hContext, 0, migdata, phObject))) {
		free(migdata);
		return result;
	}

	return TSS_SUCCESS;
}
