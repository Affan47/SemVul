ohash_table_lookup_extended(const ohash_table_t *oh, const void *key,
	void *okey, void *oval)
{
	struct ohash_pair pk;
	const void *hkey;

	ohash_table_check(oh);

	pk.oh = oh;
	pk.key = key;

	if (hash_list_find(oh->hl, &pk, &hkey)) {
		const struct ohash_pair *op = hkey;
		g_assert(op->oh == oh);
		if (okey != NULL)
			*(void **) okey = deconstify_pointer(op->key);
		if (oval != NULL)
			*(void **) oval = deconstify_pointer(op->value);
		return TRUE;
	} else {
		return FALSE;
	}
}
