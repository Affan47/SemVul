copy_to_part_field_buffers(Field **ptr,
                                       uchar **field_bufs,
                                       uchar **restore_ptr)
{
  Field *field;
  while ((field= *(ptr++)))
  {
    *restore_ptr= field->ptr;
    restore_ptr++;
    if (!field->maybe_null() || !field->is_null())
    {
      CHARSET_INFO *cs= ((Field_str*)field)->charset();
      uint max_len= field->pack_length();
      uint data_len= field->data_length();
      uchar *field_buf= *field_bufs;


      if (field->type() == MYSQL_TYPE_VARCHAR)
      {
        uint len_bytes= ((Field_varstring*)field)->length_bytes;
        my_strnxfrm(cs, field_buf + len_bytes, max_len,
                    field->ptr + len_bytes, data_len);
        if (len_bytes == 1)
          *field_buf= (uchar) data_len;
        else
          int2store(field_buf, data_len);
      }
      else
      {
        my_strnxfrm(cs, field_buf, max_len,
                    field->ptr, max_len);
      }
      field->ptr= field_buf;
    }
    field_bufs++;
  }
  return;
}
