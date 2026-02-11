k_int2str(struct sample *smp, union stktable_key_data *kdata, size_t *len)
{
	void *key;

	key = (void *)ultoa_r(smp->data.uint, kdata->buf, *len);
	if (!key)
		return NULL;

	*len = strlen((const char *)key);
	return key;
}
