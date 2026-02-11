ho_bitmap_set_height (const ho_bitmap * m, const int height, const int top,
  const int bottom)
{
  ho_bitmap *m_out;
  int x, y, locale_top, locale_bottom, locale_height;


  m_out = ho_bitmap_new (m->width, m->height);
  if (!m_out)
    return NULL;

  m_out->x = m->x;
  m_out->y = m->y;

  m_out->type = m->type;
  m_out->font_height = m->font_height;
  m_out->font_width = m->font_width;
  m_out->font_spacing = m->font_spacing;
  m_out->line_spacing = m->line_spacing;
  m_out->avg_line_fill = m->avg_line_fill;
  m_out->com_line_fill = m->com_line_fill;
  m_out->nikud = m->nikud;


  for (x = 0; x < m->width; x++)
    for (y = 0; y < m->height; y++)
    {


      if (ho_bitmap_get (m, x, y))
      {
        locale_height = height;
        locale_top = top;
        locale_bottom = bottom;

        if (y - top < 0)
          locale_top = y;
        if (y + height + bottom > m->height)
        {
          locale_bottom = 0;
          locale_height = m->height - y - 1;
        }

        ho_bitmap_draw_vline (m_out, x, y - locale_top,
          locale_height + locale_bottom);
        y = m->height;
      }
    }

  return m_out;
}
