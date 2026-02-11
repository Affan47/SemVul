mc_get_uuid_by_pub(TCPA_STORE_PUBKEY *pub)
{
	TSS_UUID *ret;
	struct key_mem_cache *tmp;

	for (tmp = key_mem_cache_head; tmp; tmp = tmp->next) {
		LogDebugFn("TCSD mem_cached handle: 0x%x", tmp->tcs_handle);
		if (tmp->blob &&
		    tmp->blob->pubKey.keyLength == pub->keyLength &&
		    !memcmp(tmp->blob->pubKey.key, pub->key, pub->keyLength)) {
			ret = &tmp->uuid;
			return ret;
		}
	}

	return NULL;
}
