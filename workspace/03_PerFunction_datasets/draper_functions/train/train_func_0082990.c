freeCacheChar( char*& ptr )
{
  if( ptr != NULL )
    {
      delete [] ptr;
      ptr = NULL;
    }
}
