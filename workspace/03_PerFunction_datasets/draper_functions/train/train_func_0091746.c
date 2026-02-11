hash_print_stats (struct hash_table_s *ht, FILE *out_FILE)
{
  fprintf (out_FILE, "Load=%ld/%ld=%.0f%%, ", ht->ht_fill, ht->ht_size,
	   100.0 * (double) ht->ht_fill / (double) ht->ht_size);
  fprintf (out_FILE, "Rehash=%d, ", ht->ht_rehashes);
  fprintf (out_FILE, "Collisions=%ld/%ld=%.0f%%\n",
	   ht->ht_collisions, ht->ht_lookups,
	   (ht->ht_lookups
	    ? (100.0 * (double) ht->ht_collisions / (double) ht->ht_lookups)
	    : 0));
}
