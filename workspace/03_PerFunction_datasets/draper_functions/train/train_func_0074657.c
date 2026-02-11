_new_HashTable(HashMemory *mem, int size, HashCase hcase,
			 void *app_data, HASH_DEL_FN(*del_fn))
{
  HashTable *hash;
  int allocate_mem = !mem;
  int i;


  if(size <= 0) {
    errno = EINVAL;
    return NULL;
  };


  if(allocate_mem) {
    mem = _new_HashMemory(1, 100);
    if(!mem)
      return NULL;
  };


  hash = (HashTable *) _new_FreeListNode(mem->hash_memory);
  if(!hash) {
    errno = ENOMEM;
    if(allocate_mem)
      mem = _del_HashMemory(mem, 1);
    return NULL;
  };


  hash->mem = mem;
  hash->internal_mem = allocate_mem;
  hash->case_sensitive = hcase==HONOUR_CASE;
  hash->size = size;
  hash->bucket = NULL;
  hash->keycmp = hash->case_sensitive ? _ht_strcmp : _ht_lower_strcmp;
  hash->app_data = app_data;
  hash->del_fn = del_fn;


  hash->bucket = (HashBucket *) malloc(sizeof(HashBucket) * size);
  if(!hash->bucket) {
    errno = ENOMEM;
    return _del_HashTable(hash);
  };


  for(i=0; i<size; i++) {
    HashBucket *b = hash->bucket + i;
    b->head = NULL;
    b->count = 0;
  };


  return hash;
}
