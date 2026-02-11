getopt_ll_limit_value(longlong num, const struct my_option *optp,
                               my_bool *fix)
{
  longlong old= num;
  my_bool adjusted= FALSE;
  char buf1[255], buf2[255];
  ulonglong block_size= (optp->block_size ? (ulonglong) optp->block_size : 1L);

  if (num > 0 && ((ulonglong) num > (ulonglong) optp->max_value) &&
      optp->max_value)
  {
    num= (ulonglong) optp->max_value;
    adjusted= TRUE;
  }

  switch ((optp->var_type & GET_TYPE_MASK)) {
  case GET_INT:
    if (num > (longlong) INT_MAX)
    {
      num= ((longlong) INT_MAX);
      adjusted= TRUE;
    }
    break;
  case GET_LONG:
#if SIZEOF_LONG < SIZEOF_LONG_LONG
    if (num > (longlong) LONG_MAX)
    {
      num= ((longlong) LONG_MAX);
      adjusted= TRUE;
    }
#endif
    break;
  default:
    DBUG_ASSERT((optp->var_type & GET_TYPE_MASK) == GET_LL);
    break;
  }

  num= (num / block_size);
  num= (longlong) (num * block_size);

  if (num < optp->min_value)
  {
    num= optp->min_value;
    if (old < optp->min_value)
      adjusted= TRUE;
  }

  if (fix)
    *fix= old != num;
  else if (adjusted)
    my_getopt_error_reporter(WARNING_LEVEL,
                             "option '%s': signed value %s adjusted to %s",
                             optp->name, llstr(old, buf1), llstr(num, buf2));
  return num;
}
