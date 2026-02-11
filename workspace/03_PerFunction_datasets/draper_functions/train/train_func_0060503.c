do_cut_string(Copy_field *copy)
{
  CHARSET_INFO *cs= copy->from_field->charset();
  memcpy(copy->to_ptr,copy->from_ptr,copy->to_length);


  if (cs->cset->scan(cs,
                     (char*) copy->from_ptr + copy->to_length,
                     (char*) copy->from_ptr + copy->from_length,
                     MY_SEQ_SPACES) < copy->from_length - copy->to_length)
  {
    copy->to_field->set_warning(MYSQL_ERROR::WARN_LEVEL_WARN,
                                WARN_DATA_TRUNCATED, 1);
  }
}
