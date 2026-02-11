fread_buff( libspectrum_byte *ptr, size_t size, int how )
{
  size_t s;
  size_t n;

  if( how == INTO_BUFF ) {
    n = size > FBUFF_SIZE ? FBUFF_SIZE : size;

    s = fread( fbuff, n, 1, inp_file );
    if( s != 1 ) return s;
    fbuff_size = n;
    memcpy( ptr, fbuff, n );
    if( size > FBUFF_SIZE ) {
      ptr += n;
      n = size - FBUFF_SIZE;
      return fread( ptr, n, 1, inp_file );
    }
  } else {
    n = size <= fbuff_size ? size : fbuff_size;

    if( n > 0 ) {
      memcpy( ptr, fbuff, n );
      if( n < fbuff_size )
        memmove( fbuff, fbuff + n, fbuff_size - n );
      fbuff_size -= n;
      size -= n;
      ptr += n;
    }
    if( size > 0 ) {
      return fread( ptr, size, 1, inp_file );
    }
  }
  return 1;
}
