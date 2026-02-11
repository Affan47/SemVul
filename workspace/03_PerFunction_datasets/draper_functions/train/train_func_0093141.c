store(longlong nr, bool unsigned_val)
{
  ASSERT_COLUMN_MARKED_FOR_WRITE;
  int error= 0;

  if (unsigned_flag)
  {
    if (nr < 0 && !unsigned_val)
    {
      int3store(ptr,0);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else if ((ulonglong) nr >= (ulonglong) (long) (1L << 24))
    {
      long tmp= (long) (1L << 24)-1L;
      int3store(ptr,tmp);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else
      int3store(ptr,(uint32) nr);
  }
  else
  {
    if (nr < 0 && unsigned_val)
      nr= (ulonglong) (long) (1L << 24);

    if (nr < (longlong) INT_MIN24)
    {
      long tmp= (long) INT_MIN24;
      int3store(ptr,tmp);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else if (nr > (longlong) INT_MAX24)
    {
      long tmp=(long) INT_MAX24;
      int3store(ptr,tmp);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else
      int3store(ptr,(long) nr);
  }
  return error;
}
