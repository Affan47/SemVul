describe_pointer (GCObject *obj)
{
	HashEntry *entry;
	int i;

	for (i = 0; i < dyn_array_ptr_size (&registered_bridges); ++i) {
		if (obj == dyn_array_ptr_get (&registered_bridges, i)) {
			printf ("Pointer is a registered bridge object.\n");
			break;
		}
	}

	entry = (HashEntry *)sgen_hash_table_lookup (&hash_table, obj);
	if (!entry)
		return;

	printf ("Bridge hash table entry %p:\n", entry);
	printf ("  is bridge: %d\n", (int)entry->is_bridge);
	printf ("  is visited: %d\n", (int)entry->v.dfs1.is_visited);
}
