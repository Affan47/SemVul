PutFlush(SOCKET sk, char *buf,size_t len)
{
  if( _left_buffer_size < len && p){
    if( FlushOut(sk) < 0) return -1;
  }

  for(; _left_buffer_size < len; )
    if( _realloc_buffer() < 0) return -3;

  memcpy(b + p, buf, len);
  p += len;
  return FlushOut(sk);
}
