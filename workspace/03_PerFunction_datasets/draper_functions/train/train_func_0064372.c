get_data_size()
{
  int const type_code= get_type_code();

  uchar buf[sizeof(m_width) + 1];
  uchar *end= net_store_length(buf, m_width);

  DBUG_EXECUTE_IF("old_row_based_repl_4_byte_map_id_master",
                  return 6 + no_bytes_in_map(&m_cols) + (end - buf) +
                  (type_code == UPDATE_ROWS_EVENT ? no_bytes_in_map(&m_cols_ai) : 0) +
                  (m_rows_cur - m_rows_buf););
  int data_size= ROWS_HEADER_LEN;
  data_size+= no_bytes_in_map(&m_cols);
  data_size+= (uint) (end - buf);

  if (type_code == UPDATE_ROWS_EVENT)
    data_size+= no_bytes_in_map(&m_cols_ai);

  data_size+= (uint) (m_rows_cur - m_rows_buf);
  return data_size;
}
