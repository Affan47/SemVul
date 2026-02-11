get_date(MYSQL_TIME *res, uint fuzzydate)
{
  if (state == TIME_VALUE)
  {
    *res= value.time;
    return 0;
  }
  return Item::get_date(res, fuzzydate);
}
