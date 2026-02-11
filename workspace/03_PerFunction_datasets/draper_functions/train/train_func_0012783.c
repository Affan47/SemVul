ht_walk(htable_t ht, void (*action)(void *))
{
  unsigned int i;

  for(i = 0 ; i < ht->nbuckets ; i++) {
    struct entry *entry;

    for(entry = ht->buckets[i] ; entry ; entry = entry->next)
      action(entry->data);
  }
}
