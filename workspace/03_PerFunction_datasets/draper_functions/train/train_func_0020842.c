_hb_buffer_serialize_glyphs_text (hb_buffer_t *buffer,
				  unsigned int start,
				  unsigned int end,
				  char *buf,
				  unsigned int buf_size,
				  unsigned int *buf_consumed,
				  hb_font_t *font,
				  hb_buffer_serialize_flags_t flags)
{
  hb_glyph_info_t *info = hb_buffer_get_glyph_infos (buffer, NULL);
  hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (buffer, NULL);

  *buf_consumed = 0;
  for (unsigned int i = start; i < end; i++)
  {
    char b[1024];
    char *p = b;


    if (i)
      *p++ = '|';

    if (!(flags & HB_BUFFER_SERIALIZE_FLAG_NO_GLYPH_NAMES))
    {
      hb_font_glyph_to_string (font, info[i].codepoint, p, 128);
      p += strlen (p);
    }
    else
      p += MAX (0, snprintf (p, ARRAY_LENGTH (b) - (p - b), "%u", info[i].codepoint));

    if (!(flags & HB_BUFFER_SERIALIZE_FLAG_NO_CLUSTERS)) {
      p += MAX (0, snprintf (p, ARRAY_LENGTH (b) - (p - b), "=%u", info[i].cluster));
    }

    if (!(flags & HB_BUFFER_SERIALIZE_FLAG_NO_POSITIONS))
    {
      if (pos[i].x_offset || pos[i].y_offset)
	p += MAX (0, snprintf (p, ARRAY_LENGTH (b) - (p - b), "@%d,%d", pos[i].x_offset, pos[i].y_offset));

      *p++ = '+';
      p += MAX (0, snprintf (p, ARRAY_LENGTH (b) - (p - b), "%d", pos[i].x_advance));
      if (pos[i].y_advance)
	p += MAX (0, snprintf (p, ARRAY_LENGTH (b) - (p - b), ",%d", pos[i].y_advance));
    }

    unsigned int l = p - b;
    if (buf_size > l)
    {
      memcpy (buf, b, l);
      buf += l;
      buf_size -= l;
      *buf_consumed += l;
      *buf = '\0';
    } else
      return i - start;
  }

  return end - start;
}
