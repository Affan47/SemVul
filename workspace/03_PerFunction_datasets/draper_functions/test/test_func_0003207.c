val_str(String *str)
{
  MYSQL_TIME ltime;
  date_time_format_types format;

  val_datetime(&ltime, &format);

  if (null_value)
    return 0;

  if (!make_datetime_with_warn(format, &ltime, str))
    return str;

  null_value= 1;
  return 0;
}
