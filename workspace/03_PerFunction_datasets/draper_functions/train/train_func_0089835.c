hash_set_value (hash_table *htab,
                const void *key, size_t keylen,
                void *data)
{
  unsigned long int hval = compute_hashval (key, keylen);
  hash_entry *table = htab->table;
  size_t idx = lookup (htab, key, keylen, hval);

  if (table[idx].used)
    {

      table[idx].data = data;
      return 0;
    }
  else
    {

      void *keycopy = obstack_copy (&htab->mem_pool, key, keylen);
      insert_entry_2 (htab, keycopy, keylen, hval, idx, data);
      if (100 * htab->filled > 75 * htab->size)

        resize (htab);
      return 0;
    }
}
