hhash_sorted_iter_key(hhash_iter_t* i, uint16_t* len)
{
	if (hhash_iter_finished(i)) {
		return NULL;
	}

	void *key = hhash_sorted_iter_item(i);
	*len = key_readlen(key);
	return KEY_STR(key);
}
