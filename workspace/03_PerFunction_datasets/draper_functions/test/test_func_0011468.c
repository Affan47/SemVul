clear_caches (void)
{
	if (!lookup_string_pool)
		return;

	if (debug_lookup_caches)
		g_printerr ("Clearing lookup caches [%ld]\n", (long)total_cache_size);

	total_cache_size = 0;


	g_hash_table_destroy (linear_hlookup_string_cache);
	linear_hlookup_string_cache = NULL;

	g_hash_table_destroy (linear_hlookup_float_cache);
	linear_hlookup_float_cache = NULL;

	g_hash_table_destroy (linear_hlookup_bool_cache);
	linear_hlookup_bool_cache = NULL;


	g_hash_table_destroy (linear_vlookup_string_cache);
	linear_vlookup_string_cache = NULL;

	g_hash_table_destroy (linear_vlookup_float_cache);
	linear_vlookup_float_cache = NULL;

	g_hash_table_destroy (linear_vlookup_bool_cache);
	linear_vlookup_bool_cache = NULL;


	g_hash_table_destroy (bisection_hlookup_string_cache);
	bisection_hlookup_string_cache = NULL;

	g_hash_table_destroy (bisection_hlookup_float_cache);
	bisection_hlookup_float_cache = NULL;

	g_hash_table_destroy (bisection_hlookup_bool_cache);
	bisection_hlookup_bool_cache = NULL;


	g_hash_table_destroy (bisection_vlookup_string_cache);
	bisection_vlookup_string_cache = NULL;

	g_hash_table_destroy (bisection_vlookup_float_cache);
	bisection_vlookup_float_cache = NULL;

	g_hash_table_destroy (bisection_vlookup_bool_cache);
	bisection_vlookup_bool_cache = NULL;


	g_string_chunk_free (lookup_string_pool);
	lookup_string_pool = NULL;

	go_mem_chunk_destroy (lookup_float_pool, TRUE);
	lookup_float_pool = NULL;
}
