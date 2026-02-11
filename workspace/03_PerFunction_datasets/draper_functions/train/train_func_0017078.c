htab_find_slot_with_hash (htab_t htab, const PTR element,
                          hashval_t hash, enum insert_option insert)
{
  PTR *first_deleted_slot;
  hashval_t index, hash2;
  size_t size;
  PTR entry;

  size = htab_size (htab);
  if (insert == INSERT && size * 3 <= htab->n_elements * 4)
    {
      if (htab_expand (htab) == 0)
	return NULL;
      size = htab_size (htab);
    }

  index = htab_mod (hash, htab);

  htab->searches++;
  first_deleted_slot = NULL;

  entry = htab->entries[index];
  if (entry == HTAB_EMPTY_ENTRY)
    goto empty_entry;
  else if (entry == HTAB_DELETED_ENTRY)
    first_deleted_slot = &htab->entries[index];
  else if ((*htab->eq_f) (entry, element))
    return &htab->entries[index];

  hash2 = htab_mod_m2 (hash, htab);
  for (;;)
    {
      htab->collisions++;
      index += hash2;
      if (index >= size)
	index -= size;

      entry = htab->entries[index];
      if (entry == HTAB_EMPTY_ENTRY)
	goto empty_entry;
      else if (entry == HTAB_DELETED_ENTRY)
	{
	  if (!first_deleted_slot)
	    first_deleted_slot = &htab->entries[index];
	}
      else if ((*htab->eq_f) (entry, element))
	return &htab->entries[index];
    }

 empty_entry:
  if (insert == NO_INSERT)
    return NULL;

  if (first_deleted_slot)
    {
      htab->n_deleted--;
      *first_deleted_slot = HTAB_EMPTY_ENTRY;
      return first_deleted_slot;
    }

  htab->n_elements++;
  return &htab->entries[index];
}
