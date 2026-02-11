_clear_HashTable(HashTable *hash)
{
  int i;


  if(!hash)
    return 1;


  for(i=0; i<hash->size; i++) {
    HashBucket *bucket = hash->bucket + i;


    HashNode *node = bucket->head;
    while(node) {
      HashNode *next = node->next;
      (void) _del_HashNode(hash, node);
      node = next;
    };


    bucket->head = NULL;
    bucket->count = 0;
  };
  return 0;
}
