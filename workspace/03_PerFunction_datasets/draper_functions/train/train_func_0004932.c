hset_create(enum hash_key_type ktype, size_t keysize)
{
	hset_t *hx;

	g_assert(ktype != HASH_KEY_ANY);

	hx = hset_allocate(HASH_MIN_BITS, FALSE);
	hash_keyhash_setup(&hx->kset, ktype, keysize);

	return hx;
}
