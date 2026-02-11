sgen_hash_table_clean (SgenHashTable *hash_table)
{
	guint i;

	if (!hash_table->size) {
		g_assert (!hash_table->table);
		g_assert (!hash_table->num_entries);
		return;
	}

	for (i = 0; i < hash_table->size; ++i) {
		SgenHashTableEntry *entry = hash_table->table [i];
		while (entry) {
			SgenHashTableEntry *next = entry->next;
			sgen_free_internal (entry, hash_table->entry_mem_type);
			entry = next;
		}
	}

	sgen_free_internal_dynamic (hash_table->table, hash_table->size * sizeof (SgenHashTableEntry*), hash_table->table_mem_type);

	hash_table->table = NULL;
	hash_table->size = 0;
	hash_table->num_entries = 0;
}
