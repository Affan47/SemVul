update_row_values(TABLE *table,
                                               const unsigned char *,
                                               unsigned char *,
                                               Field **fields)
{
  Field *f;
  enum_yes_no value;

  for (; (f= *fields) ; fields++)
  {
    if (bitmap_is_set(table->write_set, f->field_index))
    {
      switch(f->field_index)
      {
      case 0:
        return HA_ERR_WRONG_COMMAND;
      case 1:
        value= (enum_yes_no) get_field_enum(f);
        *m_row.m_enabled_ptr= (value == ENUM_YES) ? true : false;
        break;
      case 2:
        if (m_row.m_timed_ptr)
        {
          value= (enum_yes_no) get_field_enum(f);
          *m_row.m_timed_ptr= (value == ENUM_YES) ? true : false;
        }
        break;
      default:
        DBUG_ASSERT(false);
      }
    }
  }

  return 0;
}
