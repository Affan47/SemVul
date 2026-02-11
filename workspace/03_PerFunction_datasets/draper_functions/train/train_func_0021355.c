jbg_strerror(int errnum)
{
  errnum >>= 4;
  if (errnum < 0 || (unsigned) errnum >= sizeof(errmsg)/sizeof(errmsg[0]))
    return "Unknown error code passed to jbg_strerror()";

  return errmsg[errnum];
}
