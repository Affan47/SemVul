htab_find_with_hash (htab_t htab, const PTR element, hashval_t hash)
{
  hashval_t index, hash2;
  size_t size;
  PTR entry;

  htab->searches++;
  size = htab_size (htab);
  index = htab_mod (hash, htab);

  entry = htab->entries[index];
  if (entry == HTAB_EMPTY_ENTRY
      || (entry != HTAB_DELETED_ENTRY && (*htab->eq_f) (entry, element)))
    return entry;

  hash2 = htab_mod_m2 (hash, htab);
  for (;;)
    {
      htab->collisions++;
      index += hash2;
      if (index >= size)
	index -= size;

      entry = htab->entries[index];
      if (entry == HTAB_EMPTY_ENTRY
	  || (entry != HTAB_DELETED_ENTRY && (*htab->eq_f) (entry, element)))
	return entry;
    }
}
