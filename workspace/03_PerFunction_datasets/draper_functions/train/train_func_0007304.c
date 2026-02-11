get_placeholder_row()
{
  iterator result;


  const int rows_count = get_internal_rows_count();
  if(rows_count)
  {
    type_datamodel_row_index row = rows_count - 1;


    while((m_map_rows.find(row) != m_map_rows.end()) && m_map_rows[row].m_removed)
    {
      if(row)
        --row;
      else
      {
        std::cerr << G_STRFUNC << ": Placeholder row not found." << std::endl;
        return result;
      }
    }

    type_map_rows::const_iterator iter_map = m_map_rows.find(row);
    if(iter_map != m_map_rows.end())
    {

      create_iterator(row, result);
    }
  }

  return result;
}
