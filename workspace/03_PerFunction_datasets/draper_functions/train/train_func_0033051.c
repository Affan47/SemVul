zrleBufferAlloc(zrleBuffer *buffer, int size)
{
  buffer->ptr = buffer->start = malloc(size);
  if (buffer->start == NULL) {
    buffer->end = NULL;
    return FALSE;
  }

  buffer->end = buffer->start + size;

  return TRUE;
}
