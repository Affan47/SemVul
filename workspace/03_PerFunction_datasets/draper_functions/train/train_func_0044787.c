reverse_range (hb_buffer_t *buffer,
	       unsigned int start,
	       unsigned int end)
{
  unsigned int i, j;

  for (i = start, j = end - 1; i < j; i++, j--) {
    hb_internal_glyph_info_t t;

    t = buffer->in_string[i];
    buffer->in_string[i] = buffer->in_string[j];
    buffer->in_string[j] = t;
  }

  if (buffer->positions) {
    for (i = 0, j = end - 1; i < j; i++, j--) {
      hb_internal_glyph_position_t t;

      t = buffer->positions[i];
      buffer->positions[i] = buffer->positions[j];
      buffer->positions[j] = t;
    }
  }
}
