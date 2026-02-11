hikset_key_hash(const void *value, void *data)
{
	hikset_t *hik = data;
	const void * const *key = value;

	hikset_check(hik);

	return NULL == hik->ihash ?
		binary_hash(*key, hik->uik.keysize) :
		(*hik->ihash)(*key);
}
