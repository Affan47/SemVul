do_cut_string_complex(Copy_field *copy)
{
  int well_formed_error;
  CHARSET_INFO *cs= copy->from_field->charset();
  const uchar *from_end= copy->from_ptr + copy->from_length;
  uint copy_length= cs->cset->well_formed_len(cs,
                                              (char*) copy->from_ptr,
                                              (char*) from_end,
                                              copy->to_length / cs->mbmaxlen,
                                              &well_formed_error);
  if (copy->to_length < copy_length)
    copy_length= copy->to_length;
  memcpy(copy->to_ptr, copy->from_ptr, copy_length);


  if (well_formed_error ||
      cs->cset->scan(cs, (char*) copy->from_ptr + copy_length,
                     (char*) from_end,
                     MY_SEQ_SPACES) < (copy->from_length - copy_length))
  {
    copy->to_field->set_warning(MYSQL_ERROR::WARN_LEVEL_WARN,
                                WARN_DATA_TRUNCATED, 1);
  }

  if (copy_length < copy->to_length)
    cs->cset->fill(cs, (char*) copy->to_ptr + copy_length,
                   copy->to_length - copy_length, ' ');
}
