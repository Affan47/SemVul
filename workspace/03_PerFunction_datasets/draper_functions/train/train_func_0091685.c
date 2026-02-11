hash_keyhash_data_setup(struct hkeys *hk,
	hash_data_fn_t hash, void *data, eq_data_fn_t eq)
{
	g_assert(hk != NULL);
	g_assert(hash != NULL);
	g_assert(eq != NULL);

	hk->type = HASH_KEY_ANY_DATA;
	hk->uh.hd.hash = hash;
	hk->uh.hd.data = data;
	hk->uk.eq_data = eq;
}
