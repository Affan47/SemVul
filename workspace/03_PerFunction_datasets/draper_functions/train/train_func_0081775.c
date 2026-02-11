bgav_bytebuffer_append_data(bgav_bytebuffer_t * b, uint8_t * data, int len, int padding)
  {
  if(b->size + len + padding > b->alloc)
    {
    b->alloc = b->size + len + padding + 1024;
    b->buffer = realloc(b->buffer, b->alloc);
    }
  memcpy(b->buffer + b->size, data, len);
  b->size += len;

  if(padding)
    memset(b->buffer + b->size, 0, padding);
  }
