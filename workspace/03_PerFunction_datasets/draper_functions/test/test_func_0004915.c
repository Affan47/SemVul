HT_get( ConstHashTable table, const char *key, int keylen, HashSum hash )
{
  HashNode node;
  int cmp;

  DEBUG( MAIN, ("HT_get( %p, %p, %d, 0x%08lX )\n", table, key, keylen, hash) );

  assert( table != NULL );
  assert( key   != NULL );

  AssertValidPtr( table );

  if( table->count == 0 )
    return NULL;

  if( hash == 0 ) {
    if( keylen )
      HASH_DATA( hash, keylen, key );
    else
      HASH_STR_LEN( hash, key, keylen );
  }

  node = table->root[hash & table->bmask];

  DEBUG( MAIN, ("key [%s] hash 0x%08lX bucket %lu/%d\n",
                key, hash, (hash & table->bmask) + 1U, 1<<table->size) );

  while( node ) {
    DEBUG( MAIN, ("node=%p (key=[%s] len=%d hash=0x%08lX)\n",
                  node, node->key, node->keylen, node->hash) );

    if( ENTRY_FOUND_HKL( node ) ) {
      DEBUG( MAIN, ("hash element found\n") );
      break;
    }

    DEBUG( MAIN, ("cmp: %d\n", cmp) );

    if( cmp < 0 ) {
      DEBUG( MAIN, ("cannot find hash element\n") );
      return NULL;
    }

    DEBUG( MAIN, ("advancing to next hash element\n") );
    node = node->next;
  }

#ifdef DEBUG_UTIL_HASH
  if( node == NULL )
    DEBUG( MAIN, ("hash element not found\n") );
  else
    DEBUG( MAIN, ("successfully found [%s] in hash table\n", node->key) );
#endif

  return node ? node->pObj : NULL;
}
