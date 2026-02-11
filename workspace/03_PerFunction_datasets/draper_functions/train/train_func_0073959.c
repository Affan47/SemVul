mailstream_write(mailstream * s, const void * buf, size_t count)
{
  int r;

  if (s == NULL)
    return -1;

  if (count + s->write_buffer_len > s->buffer_max_size) {
    r = mailstream_flush(s);
    if (r == -1)
      return -1;

    if (count > s->buffer_max_size)
      return write_direct(s, buf, count);
  }

  return write_to_internal_buffer(s, buf, count);
}
