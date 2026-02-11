val_str_ascii(String *str)
{
  DBUG_ASSERT(fixed == 1);
  const char *format_name;
  KNOWN_DATE_TIME_FORMAT *format;
  String *val= args[0]->val_str_ascii(str);
  ulong val_len;

  if ((null_value= args[0]->null_value))
    return 0;

  val_len= val->length();
  for (format= &known_date_time_formats[0];
       (format_name= format->format_name);
       format++)
  {
    uint format_name_len;
    format_name_len= (uint) strlen(format_name);
    if (val_len == format_name_len &&
	!my_strnncoll(&my_charset_latin1,
		      (const uchar *) val->ptr(), val_len,
		      (const uchar *) format_name, val_len))
    {
      const char *format_str= get_date_time_format_str(format, type);
      str->set(format_str, (uint) strlen(format_str), &my_charset_numeric);
      return str;
    }
  }

  null_value= 1;
  return 0;
}
