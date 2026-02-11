movie_add_sound( libspectrum_signed_word *buff, int len )
{
  while( len ) {
    if( stereo == 'S' ) {
      add_sound( buff, len > 131072 ? 65536 : len >> 1 );
      buff += len > 131072 ? 131072 : len;
      len -= len > 131072 ? 131072 : len;
    } else {
      add_sound( buff, len > 65536 ? 65536 : len );
      buff += len > 65536 ? 65536 : len;
      len -= len > 65536 ? 65536 : len;
    }
  }
}
