gtkhash_hash_func_deinit_all(struct hash_func_s *funcs)
{
	g_assert(funcs);

	for (int i = 0; i < HASH_FUNCS_N; i++)
		gtkhash_hash_func_deinit(&funcs[i]);
}
