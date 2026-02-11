get_virama_glyph (hb_font_t *font, hb_codepoint_t *pglyph) const
  {
    hb_codepoint_t glyph = virama_glyph;
    if (unlikely (virama_glyph == (hb_codepoint_t) -1))
    {
      if (!config->virama || !font->get_glyph (config->virama, 0, &glyph))
	glyph = 0;


      (const_cast<indic_shape_plan_t *> (this))->virama_glyph = glyph;
    }

    *pglyph = glyph;
    return glyph != 0;
  }
