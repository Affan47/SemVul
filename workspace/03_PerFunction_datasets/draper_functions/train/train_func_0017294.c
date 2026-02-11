add_char (struct grub_font_info *font_info, FT_Face face,
	  grub_uint32_t char_code, int nocut)
{
  FT_UInt glyph_idx;
  struct glyph_replace *cur;

  glyph_idx = FT_Get_Char_Index (face, char_code);
  if (!glyph_idx)
    return;
  add_glyph (font_info, glyph_idx, face, char_code, nocut);
  for (cur = subst_rightjoin; cur; cur = cur->next)
    if (cur->from == glyph_idx)
      {
	add_glyph (font_info, cur->to, face,
		   char_code | GRUB_FONT_CODE_RIGHT_JOINED, nocut);
	break;
      }
  if (!cur && char_code >= GRUB_UNICODE_ARABIC_START
      && char_code < GRUB_UNICODE_ARABIC_END)
    {
      int i;
      for (i = 0; grub_unicode_arabic_shapes[i].code; i++)
	if (grub_unicode_arabic_shapes[i].code == char_code
	    && grub_unicode_arabic_shapes[i].right_linked)
	  {
	    FT_UInt idx2;
	    idx2 = FT_Get_Char_Index (face, grub_unicode_arabic_shapes[i]
				      .right_linked);
	    if (idx2)
	      add_glyph (font_info, idx2, face,
			 char_code | GRUB_FONT_CODE_RIGHT_JOINED, nocut);
	    break;
	  }

    }

  for (cur = subst_leftjoin; cur; cur = cur->next)
    if (cur->from == glyph_idx)
      {
	add_glyph (font_info, cur->to, face,
		   char_code | GRUB_FONT_CODE_LEFT_JOINED, nocut);
	break;
      }
  if (!cur && char_code >= GRUB_UNICODE_ARABIC_START
      && char_code < GRUB_UNICODE_ARABIC_END)
    {
      int i;
      for (i = 0; grub_unicode_arabic_shapes[i].code; i++)
	if (grub_unicode_arabic_shapes[i].code == char_code
	    && grub_unicode_arabic_shapes[i].left_linked)
	  {
	    FT_UInt idx2;
	    idx2 = FT_Get_Char_Index (face, grub_unicode_arabic_shapes[i]
				      .left_linked);
	    if (idx2)
	      add_glyph (font_info, idx2, face,
			 char_code | GRUB_FONT_CODE_LEFT_JOINED, nocut);
	    break;
	  }

    }
  for (cur = subst_medijoin; cur; cur = cur->next)
    if (cur->from == glyph_idx)
      {
	add_glyph (font_info, cur->to, face,
		   char_code | GRUB_FONT_CODE_LEFT_JOINED
		   | GRUB_FONT_CODE_RIGHT_JOINED, nocut);
	break;
      }
  if (!cur && char_code >= GRUB_UNICODE_ARABIC_START
      && char_code < GRUB_UNICODE_ARABIC_END)
    {
      int i;
      for (i = 0; grub_unicode_arabic_shapes[i].code; i++)
	if (grub_unicode_arabic_shapes[i].code == char_code
	    && grub_unicode_arabic_shapes[i].both_linked)
	  {
	    FT_UInt idx2;
	    idx2 = FT_Get_Char_Index (face, grub_unicode_arabic_shapes[i]
				      .both_linked);
	    if (idx2)
	      add_glyph (font_info, idx2, face,
			 char_code | GRUB_FONT_CODE_LEFT_JOINED
			 | GRUB_FONT_CODE_RIGHT_JOINED, nocut);
	    break;
	  }

    }
}
