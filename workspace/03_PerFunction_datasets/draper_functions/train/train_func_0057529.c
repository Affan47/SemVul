do_before_row_operations(const Slave_reporting_capability *const)
{
  int error= 0;


  if (get_flags(STMT_END_F))
    status_var_increment(thd->status_var.com_stat[SQLCOM_INSERT]);


  if ((slave_exec_mode == SLAVE_EXEC_MODE_IDEMPOTENT) ||
      (m_table->s->db_type()->db_type == DB_TYPE_NDBCLUSTER))
  {


    thd->lex->duplicates= DUP_REPLACE;


    thd->lex->sql_command= SQLCOM_REPLACE;


    m_table->file->extra(HA_EXTRA_IGNORE_DUP_KEY);


    m_table->file->extra(HA_EXTRA_WRITE_CAN_REPLACE);


    m_table->file->extra(HA_EXTRA_IGNORE_NO_KEY);


  }


  m_table->timestamp_field_type= TIMESTAMP_NO_AUTO_SET;


  m_table->next_number_field= m_table->found_next_number_field;


  if (!is_auto_inc_in_extra_columns())
    m_table->auto_increment_field_not_null= TRUE;
  else
  {


    m_table->auto_increment_field_not_null= FALSE;
    m_table->mark_auto_increment_column();
  }

  return error;
}
