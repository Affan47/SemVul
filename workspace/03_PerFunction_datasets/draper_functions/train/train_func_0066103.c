HT_fetchnode( HashTable table, HashNode node )
{
  HashNode *pNode;
  void *pObj;

  DEBUG( MAIN, ("HT_fetchnode( %p, %p )\n", table, node) );

  assert( table != NULL );
  assert( node  != NULL );

  AssertValidPtr( table );
  AssertValidPtr( node );

  CHANGE_STATE(table);

  pNode = &table->root[node->hash & table->bmask];

  DEBUG( MAIN, ("key [%s] hash 0x%08lX bucket %lu/%d\n",
                node->key, node->hash, (node->hash & table->bmask) + 1U, 1<<table->size) );

  while( *pNode && *pNode != node )
    pNode = &(*pNode)->next;

  if( *pNode == NULL ) {
    DEBUG( MAIN, ("hash element not found\n") );
    return NULL;
  }

  pObj   = node->pObj;
  *pNode = node->next;

  node->pObj = NULL;
  node->next = NULL;

  table->count--;

  DEBUG( MAIN, ("successfully fetched node @ %p (%d nodes still in hash table)\n",
                node, table->count) );

  CHECK_AUTOSHRINK( table );

  return pObj;
}
