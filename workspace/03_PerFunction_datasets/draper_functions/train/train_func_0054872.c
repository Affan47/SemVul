inthash_new(size_t initial_size) {
  inthash hashtable = (inthash) calloc(1, sizeof(struct_inthash));

  if (hashtable) {
    size_t size;
    for(size = MIN_LG_SIZE ; POW2(size) < initial_size ; size++) ;
    if ((hashtable->items =
         (inthash_item *) calloc(POW2(size), sizeof(inthash_item)))) {
      hashtable->lg_size = size;
    }
    hashtable->used = 0;
    hashtable->stash.size = 0;
    hashtable->pool.buffer = NULL;
    hashtable->pool.size = 0;
    hashtable->pool.capacity = 0;
    hashtable->pool.used = 0;
    hashtable->stats.max_stash_size = 0;
    hashtable->stats.write_count = 0;
    hashtable->stats.add_count = 0;
    hashtable->stats.cuckoo_moved = 0;
    hashtable->stats.stash_added= 0;
    hashtable->stats.pool_compact_count = 0;
    hashtable->stats.pool_realloc_count = 0;
    hashtable->stats.rehash_count = 0;
    hashtable->custom.value.free = NULL;
    hashtable->custom.value.arg = NULL;
    hashtable->custom.key.dup = NULL;
    hashtable->custom.key.free = NULL;
    hashtable->custom.key.hash = NULL;
    hashtable->custom.key.equals = NULL;
    hashtable->custom.key.arg = NULL;
  }
  return hashtable;
}
