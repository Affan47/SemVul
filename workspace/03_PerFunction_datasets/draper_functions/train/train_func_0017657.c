add_char(struct stringbuf *buf, char c)
{
  if (buf->ptr < buf->end) *(buf->ptr++) = c;
}
