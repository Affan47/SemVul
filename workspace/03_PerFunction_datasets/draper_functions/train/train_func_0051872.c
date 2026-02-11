gnm_dep_container_resize (GnmDepContainer *deps, int rows)
{
	int i, buckets = 1 + BUCKET_OF_ROW (rows - 1);

	for (i = buckets; i < deps->buckets; i++) {
		GHashTable *hash = deps->range_hash[i];
		if (hash != NULL) {
			int s = g_hash_table_size (hash);
			if (s)
				g_printerr ("Hash table size: %d\n", s);
			g_hash_table_destroy (hash);
			deps->range_hash[i] = NULL;
		}
	}

	deps->range_hash = g_renew (GHashTable *, deps->range_hash, buckets);

	for (i = deps->buckets; i < buckets; i++)
		deps->range_hash[i] = NULL;

	deps->buckets = buckets;
}
