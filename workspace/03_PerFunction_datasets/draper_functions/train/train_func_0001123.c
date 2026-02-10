consume_line (hb_buffer_t  *buffer,
		     const char   *text,
		     unsigned int  text_len,
		     const char   *text_before,
		     const char   *text_after)
  {
    hb_set_clear (glyphs);
    shaper.shape_closure (text, text_len, font, buffer, glyphs);

    if (hb_set_is_empty (glyphs))
      return;


    bool first = true;
    for (hb_codepoint_t i = -1; hb_set_next (glyphs, &i);)
    {
      if (first)
	first = false;
      else
	printf (" ");
      if (show_glyph_names)
      {
	char glyph_name[64];
	hb_font_glyph_to_string (font, i, glyph_name, sizeof (glyph_name));
	printf ("%s", glyph_name);
      } else
	printf ("%u", i);
    }
  }
