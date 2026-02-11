blake2b_final( blake2b_state *S, uint8_t *out, uint8_t outlen )
{
  int i;
  uint8_t buffer[BLAKE2B_OUTBYTES];

  if( S->buflen > BLAKE2B_BLOCKBYTES )
  {
    blake2b_increment_counter( S, BLAKE2B_BLOCKBYTES );
    blake2b_compress( S, S->buf );
    S->buflen -= BLAKE2B_BLOCKBYTES;
    memcpy( S->buf, S->buf + BLAKE2B_BLOCKBYTES, S->buflen );
  }

  blake2b_increment_counter( S, S->buflen );
  blake2b_set_lastblock( S );
  memset( S->buf + S->buflen, 0, 2 * BLAKE2B_BLOCKBYTES - S->buflen );
  blake2b_compress( S, S->buf );

  for( i = 0; i < 8; ++i )
    store64( buffer + sizeof( S->h[i] ) * i, S->h[i] );

  memcpy( out, buffer, outlen );
  return 0;
}
