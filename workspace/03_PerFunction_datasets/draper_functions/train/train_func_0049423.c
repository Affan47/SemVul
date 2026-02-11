val_str_ascii(String *str)
{
  DBUG_ASSERT(fixed == 1);
  MYSQL_TIME ltime;
  enum date_time_format_types format;

  if (Item_date_add_interval::get_date(&ltime, TIME_NO_ZERO_DATE))
    return 0;

  if (ltime.time_type == MYSQL_TIMESTAMP_DATE)
    format= DATE_ONLY;
  else if (ltime.second_part)
    format= DATE_TIME_MICROSECOND;
  else
    format= DATE_TIME;

  if (!make_datetime(format, &ltime, str))
    return str;

  null_value=1;
  return 0;
}
