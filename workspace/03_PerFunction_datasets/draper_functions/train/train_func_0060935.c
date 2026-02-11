pj_search_initcache( const char *filekey )

{
  int i;
  paralist *result = NULL;

  pj_acquire_lock();

  for( i = 0; result == NULL && i < cache_count; i++)
    {
      if( strcmp(filekey,cache_key[i]) == 0 )
	{
	  result = pj_clone_paralist( cache_paralist[i] );
	}
    }

  pj_release_lock();

  return result;
}
