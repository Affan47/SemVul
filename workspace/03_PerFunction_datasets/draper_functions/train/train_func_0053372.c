hash_grow (void)
{
	GHashTable *hash = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	int i, count = 0;

	for (i = 0; i < 1000; i++)
		g_hash_table_insert (hash, g_strdup_printf ("%d", i), g_strdup_printf ("x-%d", i));

	for (i = 0; i < 1000; i++){
		char buffer [30];
		gpointer value;

		sprintf (buffer, "%d", i);

		value = g_hash_table_lookup (hash, buffer);
		sprintf (buffer, "x-%d", i);
		if (strcmp (value, buffer) != 0){
			return FAILED ("Failed to lookup the key %d, the value was %s\n", i, value);
		}
	}

	if (g_hash_table_size (hash) != 1000)
		return FAILED ("Did not find 1000 elements on the hash, found %d\n", g_hash_table_size (hash));


	g_hash_table_foreach (hash, counter, &count);
	if (count != 1000){
		return FAILED ("Foreach count is not 1000");
	}

	g_hash_table_destroy (hash);
	return NULL;
}
