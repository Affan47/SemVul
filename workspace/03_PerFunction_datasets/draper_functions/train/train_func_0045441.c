insert_entry_2 (htab, key, keylen, hval, idx, data)
     hash_table *htab;
     const void *key;
     size_t keylen;
     unsigned long int hval;
     size_t idx;
     void *data;
{
  hash_entry *table = (hash_entry *) htab->table;

  table[idx].used = hval;
  table[idx].key = key;
  table[idx].keylen = keylen;
  table[idx].data = data;


  if ((hash_entry *) htab->first == NULL)
    {
      table[idx].next = &table[idx];
      htab->first = &table[idx];
    }
  else
    {
      table[idx].next = ((hash_entry *) htab->first)->next;
      ((hash_entry *) htab->first)->next = &table[idx];
      htab->first = &table[idx];
    }

  ++htab->filled;
  if (100 * htab->filled > 75 * htab->size)
    {


      unsigned long int old_size = htab->size;

      htab->size = next_prime (htab->size * 2);
      htab->filled = 0;
      htab->first = NULL;
      htab->table = (void *) xcalloc (1 + htab->size, sizeof (hash_entry));

      for (idx = 1; idx <= old_size; ++idx)
	if (table[idx].used)
	  insert_entry_2 (htab, table[idx].key, table[idx].keylen,
			  table[idx].used,
			  lookup (htab, table[idx].key, table[idx].keylen,
				  table[idx].used),
			  table[idx].data);

      free (table);
    }
}
