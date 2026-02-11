mempool_strdup( int pool, const char *string )
{
  size_t length = strlen( string ) + 1;

  char *ptr = mempool_alloc( pool, length );
  if( !ptr ) return NULL;

  memcpy( ptr, string, length );

  return ptr;
}
