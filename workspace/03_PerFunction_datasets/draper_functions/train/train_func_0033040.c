sgen_hash_table_set_key (SgenHashTable *hash_table, gpointer old_key, gpointer new_key)
{
	guint hash;
	SgenHashTableEntry *entry;

	entry = lookup (hash_table, old_key, &hash);

	if (entry) {
		entry->key = new_key;
		return TRUE;
	}

	return FALSE;
}
