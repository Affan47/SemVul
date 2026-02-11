ho_objmap_update_reading_index (ho_objmap * m,
  const unsigned char n_columns, const unsigned char dir_ltr)
{

  if (n_columns == 1)
  {
    return ho_objmap_update_reading_index_column (m, n_columns, dir_ltr);
  }


  if (n_columns == 253)
  {
    return ho_objmap_update_reading_index_line (m, n_columns, dir_ltr);
  }


  return ho_objmap_update_reading_index_multi_columns (m, n_columns, dir_ltr);

  return FALSE;
}
