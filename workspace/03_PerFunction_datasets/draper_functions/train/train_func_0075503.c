hash_insert (BablHashTable *htab,
             Babl          *item)
{
  int hash = htab->hash_func(htab, item);

  if (htab->data_table[hash] == NULL)
    {

      htab->data_table[hash] = item;
    }
  else
    {
      int it, oit, cursor = 0;

      while ((cursor < (htab->mask + 1)) && (htab->data_table[cursor] != NULL))
        ++cursor;

      htab->data_table[cursor] = item;

      for (oit = hash, it = htab->chain_table[oit]; it != -1; oit = it, it = htab->chain_table[oit])
        ;
      htab->chain_table[oit] = cursor;
    }

  htab->count++;
  return 0;
}
