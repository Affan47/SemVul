create_and_fill_bitmap (void)
{
  CoglBitmap *bitmap = create_bitmap ();
  CoglBuffer *buffer = COGL_BUFFER (cogl_bitmap_get_buffer (bitmap));
  uint8_t *map;
  unsigned int stride;

  stride = cogl_bitmap_get_rowstride (bitmap);

  map = cogl_buffer_map (buffer,
                         COGL_BUFFER_ACCESS_WRITE,
                         COGL_BUFFER_MAP_HINT_DISCARD);
  g_assert (map);

  generate_bitmap_data (map, stride);

  cogl_buffer_unmap (COGL_BUFFER (buffer));

  return bitmap;
}
