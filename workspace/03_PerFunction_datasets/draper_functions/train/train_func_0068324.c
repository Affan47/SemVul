hevset_create_any_real(size_t offset,
	hash_fn_t primary, hash_fn_t secondary, eq_fn_t eq)
{
	hevset_t *hx;

	g_assert(primary != NULL);

	hx = hevset_allocate(HASH_MIN_BITS, TRUE, offset);
	hash_keyhash_any_setup(&hx->kset, primary, secondary, eq);

	return hx;
}
