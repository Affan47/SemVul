is_one_of (NODE_T * p, ...)
{
  if (p != NO_NODE) {
    va_list vl;
    int a;
    BOOL_T match = A68_FALSE;
    va_start (vl, p);
    while ((a = va_arg (vl, int)) != STOP)
    {
      match = (BOOL_T) (match | (BOOL_T) (IS (p, a)));
    }
    va_end (vl);
    return (match);
  } else {
    return (A68_FALSE);
  }
}
