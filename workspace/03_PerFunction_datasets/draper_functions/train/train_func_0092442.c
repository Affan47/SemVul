val_str(String *val_buffer,
			   String *val_ptr __attribute__((unused)))
{
  ulonglong tmp=(ulonglong) Field_enum::val_int();
  uint bitnr=0;

  if (tmp == 0)
  {


    *val_buffer= empty_set_string;
    return val_buffer;
  }

  val_buffer->set_charset(field_charset);
  val_buffer->length(0);

  while (tmp && bitnr < (uint) typelib->count)
  {
    if (tmp & 1)
    {
      if (val_buffer->length())
	val_buffer->append(&field_separator, 1, &my_charset_latin1);
      String str(typelib->type_names[bitnr],
		 typelib->type_lengths[bitnr],
		 field_charset);
      val_buffer->append(str);
    }
    tmp>>=1;
    bitnr++;
  }
  return val_buffer;
}
