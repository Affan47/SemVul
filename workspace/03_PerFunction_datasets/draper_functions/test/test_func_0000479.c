hikset_lookup_extended(const hikset_t *ht, const void *key, void **valptr)
{
	size_t idx;

	hikset_check(ht);

	idx = hash_lookup_key(HASH(ht), &key);

	if ((size_t) -1 == idx)
		return FALSE;

	if (valptr != NULL) {
		void *kptr = deconstify_pointer(ht->kset.keys[idx]);
		*valptr = ptr_add_offset(kptr, -ht->offset);
	}

	return TRUE;
}
