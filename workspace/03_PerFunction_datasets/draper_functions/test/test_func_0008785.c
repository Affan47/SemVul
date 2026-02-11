hash_insert_at (struct hash_table* ht, void *item, void const *slot)
{
  void *old_item = *(void **) slot;
  if (HASH_VACANT (old_item))
    {
      ht->ht_fill++;
      if (old_item == 0)
	ht->ht_empty_slots--;
      old_item = item;
    }
  *(void const **) slot = item;
  if (ht->ht_empty_slots < ht->ht_size - ht->ht_capacity)
    {
      hash_rehash (ht);
      return (void *) hash_find_slot (ht, item);
    }
  else
    return (void *) slot;
}
