ho_dimentions_line_spacing (ho_bitmap * m)
{
  int return_val;
  ho_objmap *m_obj = NULL;

  ho_bitmap *m_clean = NULL;
  ho_bitmap *m_temp1 = NULL;
  ho_bitmap *m_temp2 = NULL;

  int x, y;
  int width;
  int height;
  unsigned char nikud_ret;

  int font_height = m->font_height;
  int font_width = m->font_width;
  unsigned char nikud = m->nikud;


  if (nikud)
    m_clean = ho_bitmap_filter_by_size (m,
      font_height / 2, font_height * 4, font_width / 3, font_width * 5);
  else
    m_clean = ho_bitmap_filter_by_size (m,
      font_height / 4, font_height * 4, font_width / 4, font_width * 5);


  m_temp1 = ho_bitmap_hlink (m_clean, font_width * 4);
  if (!m_temp1)
    return TRUE;
  ho_bitmap_free (m_clean);

  m_temp2 = ho_bitmap_vlink (m_temp1, font_height * 4);
  if (!m_temp2)
    return TRUE;

  ho_bitmap_andnot (m_temp2, m_temp1);
  ho_bitmap_free (m_temp1);


  for (x = font_width * 3; x < m->width; x += font_width * 3 + 2)
    for (y = 0; y < m->height; y++)
      ho_bitmap_unset (m_temp2, x, y);


  m_obj = ho_objmap_new_from_bitmap (m_temp2);
  ho_bitmap_free (m_temp2);


  return_val =
    ho_objmap_font_metrix (m_obj, font_height / 2, font_height * 4,
    font_width * 2, font_width * 4, &height, &width, &nikud_ret);

  ho_objmap_free (m_obj);


  if (height < font_height || height > font_height * 4)
    height = font_height * 1.5;

  m->line_spacing = height;

  return return_val;
}
