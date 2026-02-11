smalloc( long n, char *name, MPI_Comm comm )
{
  void *ptr;

  if( n <= 0 ) {
    fprintf( stderr, "WARNING: trying to allocate %ld bytes for array %s. ",
             n, name );
    fprintf( stderr, "returning NULL.\n" );
    return NULL;
  }

  ptr = malloc( n );
  if( ptr == NULL ) {
    fprintf( stderr, "ERROR: failed to allocate %ld bytes for array %s",
             n, name );
    MPI_Abort( comm, INSUFFICIENT_MEMORY );
  }

  return ptr;
}
