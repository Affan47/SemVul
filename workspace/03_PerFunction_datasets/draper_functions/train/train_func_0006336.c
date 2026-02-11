ho_font_cross (const ho_bitmap * m_text, const ho_bitmap * m_mask)
{
  ho_bitmap *m_out = NULL;
  ho_bitmap *m_temp = NULL;

  int x, y;
  unsigned char neighbors;

  m_out = ho_bitmap_new (m_text->width, m_text->height);
  if (!m_out)
    return NULL;

  m_temp = ho_font_thin (m_text, m_mask);
  if (!m_temp)
    return NULL;


  for (x = 1; x < m_text->width - 1; x++)
    for (y = 1; y < m_text->height - 1; y++)
    {

      if (ho_bitmap_get (m_temp, x, y))
      {

        neighbors = ho_bitmap_get (m_temp, x + 1, y + 1) +
          ho_bitmap_get (m_temp, x + 1, y) +
          ho_bitmap_get (m_temp, x + 1, y - 1) +
          ho_bitmap_get (m_temp, x - 1, y + 1) +
          ho_bitmap_get (m_temp, x - 1, y) +
          ho_bitmap_get (m_temp, x - 1, y - 1) +
          ho_bitmap_get (m_temp, x, y - 1) + ho_bitmap_get (m_temp, x, y + 1);


        if (neighbors > 2)
        {
          ho_bitmap_set (m_out, x, y);
        }
      }
    }

  ho_bitmap_free (m_temp);

  return m_out;
}
