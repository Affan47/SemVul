hash_table_ok (const Hash_table *table)
{
  struct hash_entry const *bucket;
  size_t n_buckets_used = 0;
  size_t n_entries = 0;

  for (bucket = table->bucket; bucket < table->bucket_limit; bucket++)
    {
      if (bucket->data)
	{
	  struct hash_entry const *cursor = bucket;


	  n_buckets_used++;
	  n_entries++;


	  while (cursor = cursor->next, cursor)
	    n_entries++;
	}
    }

  if (n_buckets_used == table->n_buckets_used && n_entries == table->n_entries)
    return true;

  return false;
}
