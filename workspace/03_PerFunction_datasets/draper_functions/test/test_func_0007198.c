alloc_sound_buff( size_t len )
{
  if( sound_buf_len < len ) {
    len = ( ( len * 3 / 2 ) / SOUND_CHUNK_LEN + 1 ) * SOUND_CHUNK_LEN;

    if( sound_buf_len == 0 ) {
      sound8 = malloc( len );
    } else {
      sound8 = realloc( sound8, len );
    }
    if( sound8 == NULL ) {
      printe( "\n\nMemory (re)allocation error.\n" );
      return ERR_OUTOFMEM;
    }
    sound16 = (void *)sound8;
    sound_buf_len = len;
    printi( 3, "fmf_alloc_sound(): sound buffer length: %lu\n", (unsigned long)sound_buf_len );
  }
  return 0;
}
