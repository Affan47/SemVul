ho_dimentions_get_columns (const ho_bitmap * m)
{
  int i, return_val;
  int hlink_value;
  ho_bitmap *m_cols = NULL;
  ho_bitmap *m_temp = NULL;
  ho_objmap *m_obj = NULL;
  ho_bitmap *m_clean;


  if (m->width > 120 && m->height > 120)
  {
    m_clean = ho_bitmap_clone_window (m, 30, 30, m->width - 60, m->height - 60);
    if (!m_clean)
      return 1;
  }
  else
  {

    return 1;
  }


  m_temp = ho_bitmap_vlink (m_clean, m->height / 3);
  ho_bitmap_free (m_clean);
  if (!m_temp)
    return 1;


  hlink_value = ((m->width / 100) < 30) ? 30 : m->width / 100;
  m_cols = ho_bitmap_hlink (m_temp, hlink_value);
  ho_bitmap_free (m_temp);
  if (!m_cols)
    return 1;


  m_obj = ho_objmap_new_from_bitmap (m_cols);
  ho_bitmap_free (m_cols);
  if (!m_obj)
    return 1;


  return_val = 0;
  for (i = 0; i < ho_objmap_get_size (m_obj); i++)
    if (ho_objmap_get_object (m_obj, i).width > m->width / 8)
      return_val++;

  ho_objmap_free (m_obj);

  return return_val;
}
