ho_bitmap_herode (const ho_bitmap * m, const int size)
{
  ho_bitmap *m_out;
  int x, y;
  int k;
  int l, last;


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


  memset ((void *) (m_out->data), 0xff, m_out->height * m_out->rowstride);

  for (y = 0; y < m->height; y++)
  {
    last = -size;
    for (x = 0; x < m->width; x++)
    {
      if (!ho_bitmap_get (m, x, y))
      {
        ho_bitmap_unset (m_out, x, y);
        l = (int) x - last;
        if ((l > 1) && (l < size))
        {
          if (last < 0)
            last = 0;
          for (k = last; k < x; k++)
            ho_bitmap_unset (m_out, k, y);
        }
        last = x;
      }
    }
  }

  return m_out;
}
