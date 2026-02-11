cache_value_int()
{
  if (!example)
    return false;

  value_cached= true;

  str_value_cached= false;

  MYSQL_TIME ltime;
  const bool eval_error=
    (field_type() == MYSQL_TYPE_TIME) ?
    example->get_time(&ltime) :
    example->get_date(&ltime, TIME_FUZZY_DATE);

  if (eval_error)
    int_value= 0;
  else
  {
    switch(field_type())
    {
    case MYSQL_TYPE_DATETIME:
    case MYSQL_TYPE_TIMESTAMP:
      int_value= TIME_to_ulonglong_datetime(&ltime);
      break;
    case MYSQL_TYPE_TIME:
      int_value= TIME_to_ulonglong_time(&ltime);
      break;
    default:
      int_value= TIME_to_ulonglong_date(&ltime);
      break;
    }
    if (ltime.neg)
      int_value= -int_value;
  }

  null_value= example->null_value;
  unsigned_flag= example->unsigned_flag;

  return true;
}
