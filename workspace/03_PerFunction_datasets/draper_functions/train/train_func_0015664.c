get_background_color_from_term (StThemeNode  *node,
                                CRTerm       *term,
                                ClutterColor *color)
{
  GetFromTermResult result = get_color_from_term (node, term, color);
  if (result == VALUE_NOT_FOUND)
    {
      if (term_is_transparent (term))
        {
          *color = TRANSPARENT_COLOR;
          return VALUE_FOUND;
        }
    }

  return result;
}
