hb_font_set_ppem (hb_font_t *font,
		  unsigned int x_ppem,
		  unsigned int y_ppem)
{
  if (HB_OBJECT_IS_INERT (font))
    return;

  font->x_ppem = x_ppem;
  font->y_ppem = y_ppem;
}
