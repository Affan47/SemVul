ap_resize_buffer( void * buf, const int min_size )
  {
  if( buf ) buf = realloc( buf, min_size );
  else buf = malloc( min_size );
  return buf;
  }
