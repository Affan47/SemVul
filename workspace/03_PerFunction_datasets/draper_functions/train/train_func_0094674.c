growhash (hash_table *table, unsigned long new_size)
{
  unsigned long i;
  unsigned long old_size = table->size;
  bucket *old_buckets = table->buckets;
  bucket *new_buckets;

  new_size = toprime (new_size);
  new_buckets = (bucket *) calloc(new_size, sizeof(*table->buckets));

  if (!new_buckets)
    return -1;

  table->size = new_size;
  table->buckets = new_buckets;
  table->count = 0;

  for (i = 0; i < old_size; i++)
    if (old_buckets[i].key)
      puthash (table, old_buckets[i].key, old_buckets[i].value);

  free (old_buckets);
  return 0;
}
