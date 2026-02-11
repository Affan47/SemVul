HN_new( const char *key, int keylen, HashSum hash )
{
  HashNode node;

  DEBUG( MAIN, ("HN_new( %p, %d, 0x%08lX )\n", key, keylen, hash) );

  assert( key != NULL );

  if( hash == 0 ) {
    if( keylen )
      HASH_DATA( hash, keylen, key );
    else
      HASH_STR_LEN( hash, key, keylen );
  }

  AllocF( HashNode, node, HN_SIZE_FIX + keylen + TERMINATOR_LENGTH );

  node->pObj   = NULL;
  node->next   = NULL;
  node->hash   = hash;
  node->keylen = keylen;
  memcpy( node->key, (const void *) key, keylen );
#ifndef NO_TERMINATED_KEYS
  node->key[keylen] = '\0';
#endif

  DEBUG( MAIN, ("created new hash node @ %p with key \"%s\"\n", node, key) );

  return node;
}
