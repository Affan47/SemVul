chunks_write_prime( struct state * s, uint64_t prime )
{
  struct chunks * c;
  uint64_t * addr;

  if ( !( c = s->chunk_mngr ) )
    return;


  if ( c->primes_count >= c->primes_capacity )
  {
    pthread_rwlock_wrlock( &s->thread_mngr->write_lock );

    if ( ftruncate( c->primes_fd, c->primes_size << 1ull ) < 0 )
    {
      state_error( s, "Cannot resize output size" );
    }

    if ( ( addr = mremap( c->primes_data, c->primes_size,
                          c->primes_size << 1, MREMAP_MAYMOVE ) ) == MAP_FAILED )
    {
      state_error( s, "Cannot remap output file '%s'", s->primes_file );
    }

    c->primes_data = addr;
    c->primes_size <<= 1;
    c->primes_capacity <<= 1;

    pthread_rwlock_unlock( &s->thread_mngr->write_lock );
  }

  c->primes_data[ __sync_fetch_and_add( &c->primes_count, 1 ) ] = prime;
}
