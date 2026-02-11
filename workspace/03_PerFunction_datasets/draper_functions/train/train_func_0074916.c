val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  MYSQL_TIME ltime;
  if (get_date(&ltime, TIME_FUZZY_DATE))
    return (String *) 0;
  if (str->alloc(MAX_DATE_STRING_REP_LENGTH))
  {
    null_value= 1;
    return (String *) 0;
  }
  make_date((DATE_TIME_FORMAT *) 0, &ltime, str);
  return str;
}
