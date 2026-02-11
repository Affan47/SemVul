store(longlong nr, bool unsigned_val)
{
  ASSERT_COLUMN_MARKED_FOR_WRITE;
  long tmp;
  int error= 0;
  if (nr < (longlong) -TIME_MAX_VALUE && !unsigned_val)
  {
    tmp= -TIME_MAX_VALUE;
    set_datetime_warning(MYSQL_ERROR::WARN_LEVEL_WARN,
                         ER_WARN_DATA_OUT_OF_RANGE, nr,
                         MYSQL_TIMESTAMP_TIME, 1);
    error= 1;
  }
  else if (nr > (longlong) TIME_MAX_VALUE || (nr < 0 && unsigned_val))
  {
    tmp= TIME_MAX_VALUE;
    set_datetime_warning(MYSQL_ERROR::WARN_LEVEL_WARN,
                         ER_WARN_DATA_OUT_OF_RANGE, nr,
                         MYSQL_TIMESTAMP_TIME, 1);
    error= 1;
  }
  else
  {
    tmp=(long) nr;
    if (tmp % 100 > 59 || tmp/100 % 100 > 59)
    {
      tmp=0;
      set_datetime_warning(MYSQL_ERROR::WARN_LEVEL_WARN,
                           ER_WARN_DATA_OUT_OF_RANGE, nr,
                           MYSQL_TIMESTAMP_TIME, 1);
      error= 1;
    }
  }
  int3store(ptr,tmp);
  return error;
}
