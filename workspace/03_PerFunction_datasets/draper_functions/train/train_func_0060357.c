do_before_row_operations(const Slave_reporting_capability *const)
{


  if (get_flags(STMT_END_F))
    status_var_increment(thd->status_var.com_stat[SQLCOM_DELETE]);

  if ((m_table->file->ha_table_flags() & HA_PRIMARY_KEY_REQUIRED_FOR_POSITION) &&
      m_table->s->primary_key < MAX_KEY)
  {


    return 0;
  }

  if (m_table->s->keys > 0)
  {

    m_key= (uchar*)my_malloc(m_table->key_info->key_length, MYF(MY_WME));
    if (!m_key)
      return HA_ERR_OUT_OF_MEM;
  }
  return 0;
}
