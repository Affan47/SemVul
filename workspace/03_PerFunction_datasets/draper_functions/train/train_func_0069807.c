nerr_raise_errnof (const char *func, const char *file, int lineno,
    			   int error, const char *fmt, ...)
{
  NEOERR *err;
  va_list ap;
  int l;

  err = _err_alloc();
  if (err == INTERNAL_ERR)
    return err;

  va_start(ap, fmt);
  vsnprintf (err->desc, sizeof(err->desc), fmt, ap);
  va_end(ap);

  l = strlen(err->desc);
  snprintf (err->desc + l, sizeof(err->desc)-l, ": [%d] %s", errno,
      strerror (errno));

  err->error = error;
  err->func = func;
  err->file = file;
  err->lineno = lineno;

  return err;
}
