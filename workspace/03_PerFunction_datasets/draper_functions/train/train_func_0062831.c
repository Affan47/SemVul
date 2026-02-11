store(double nr)
{
  ASSERT_COLUMN_MARKED_FOR_WRITE;
  int error= 0;
  nr=rint(nr);
  if (unsigned_flag)
  {
    if (nr < 0)
    {
      int3store(ptr,0);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else if (nr >= (double) (long) (1L << 24))
    {
      uint32 tmp=(uint32) (1L << 24)-1L;
      int3store(ptr,tmp);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else
      int3store(ptr,(uint32) nr);
  }
  else
  {
    if (nr < (double) INT_MIN24)
    {
      long tmp=(long) INT_MIN24;
      int3store(ptr,tmp);
      set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else if (nr > (double) INT_MAX24)
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
