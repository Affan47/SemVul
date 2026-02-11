resize_if_needed (MonoInternalHashTable *table)
{
	gpointer *new_table;
	gint new_size;
	gint i;

	if (table->num_entries < table->size * 3)
		return;

	new_size = g_spaced_primes_closest (table->num_entries);
	new_table = g_new0 (gpointer, new_size);

	for (i = 0; i < table->size; ++i) {
		while (table->table[i] != NULL) {
			gpointer value;
			gint hash;

			value = table->table [i];
			table->table [i] = *(table->next_value (value));

			hash = HASH (table->key_extract (value), table->hash_func, new_size);
			*(table->next_value (value)) = new_table [hash];
			new_table [hash] = value;
		}
	}

	g_free (table->table);

	table->size = new_size;
	table->table = new_table;
}
