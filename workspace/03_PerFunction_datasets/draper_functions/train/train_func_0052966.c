ho_bitmap_dilation_n (const ho_bitmap * m, const unsigned char n)
{
  ho_bitmap *m_out;
  int x, y;
  unsigned char sum;

  if (!m)
    return NULL;


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


  for (x = 1; x < m->width - 1; x++)
    for (y = 1; y < m->height - 1; y++)
    {


      if (!ho_bitmap_get (m, x, y))
      {
        sum = ho_bitmap_get (m, x - 1, y - 1) +
          ho_bitmap_get (m, x - 1, y) +
          ho_bitmap_get (m, x - 1, y + 1) +
          ho_bitmap_get (m, x, y - 1) +
          ho_bitmap_get (m, x, y + 1) +
          ho_bitmap_get (m, x + 1, y - 1) +
          ho_bitmap_get (m, x + 1, y) + ho_bitmap_get (m, x + 1, y + 1);
        if (sum >= n)
          ho_bitmap_set (m_out, x, y);
      }
      else
        ho_bitmap_set (m_out, x, y);
    }

  return m_out;
}
