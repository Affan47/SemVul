create_tmp_field(bool group, TABLE *table,
                                      uint convert_blob_len)
{
  Field *field;
  if (group)
  {


    field= new Field_string(((hybrid_type == DECIMAL_RESULT) ?
                             dec_bin_size : sizeof(double)) + sizeof(longlong),
                            0, name, &my_charset_bin);
  }
  else if (hybrid_type == DECIMAL_RESULT)
    field= Field_new_decimal::create_from_item(this);
  else
    field= new Field_double(max_length, maybe_null, name, decimals, TRUE);
  if (field)
    field->init(table);
  return field;
}
