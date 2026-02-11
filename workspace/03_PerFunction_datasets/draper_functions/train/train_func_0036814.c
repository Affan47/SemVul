read_from_internal_buffer(mailstream * s,
					 void * buf, size_t count)
{
  if (count >= s->read_buffer_len)
    count = s->read_buffer_len;
  if (count != 0)
    memcpy(buf, s->read_buffer, count);

  s->read_buffer_len -= count;
  if (s->read_buffer_len != 0)
    memmove(s->read_buffer, s->read_buffer + count,
	    s->read_buffer_len);

  return count;
}
