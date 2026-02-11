append()
{


  type_datamodel_row_index datamodel_row = get_internal_rows_count();

  ++m_count_extra_rows;


  for(unsigned int column_number = 0; column_number < m_columns_count; ++column_number)
  {


  }


  iterator iter;
  const bool iter_is_valid = create_iterator(datamodel_row, iter);
  if(iter_is_valid)
  {
    row_inserted(get_path(iter), iter);
  }

  return iter;
}
