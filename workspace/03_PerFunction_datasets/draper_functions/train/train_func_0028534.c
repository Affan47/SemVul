hb_ft_get_glyph_from_name (hb_font_t *font HB_UNUSED,
			   void *font_data,
			   const char *name, int len,
			   hb_codepoint_t *glyph,
			   void *user_data HB_UNUSED)
{
  FT_Face ft_face = (FT_Face) font_data;

  if (len < 0)
    *glyph = FT_Get_Name_Index (ft_face, (FT_String *) name);
  else {

    char buf[128];
    len = MIN (len, (int) sizeof (buf) - 1);
    strncpy (buf, name, len);
    buf[len] = '\0';
    *glyph = FT_Get_Name_Index (ft_face, buf);
  }

  if (*glyph == 0)
  {

    char buf[128];
    if (!FT_Get_Glyph_Name(ft_face, 0, buf, sizeof (buf)) &&
        len < 0 ? !strcmp (buf, name) : !strncmp (buf, name, len))
      return true;
  }

  return *glyph != 0;
}
