expandable_size_get_length (guint8 * ptr, guint32 array_size)
{
  gboolean next = TRUE;
  guint32 index = 0;

  while (next && index < array_size) {
    next = (ptr[index] & 0x80);
    index++;
  }
  return index;
}
