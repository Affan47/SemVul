ds_xprintf(const char *fmt, ...)
{
  Ds ds;
  va_list ap;

  ds_init(&ds);
  ds.exact_flag = 1;

  va_start(ap, fmt);
  if (ds_doprnt(&ds, 0, DS_APPEND_MODE, fmt, ap) == -1) {
	va_end(ap);
	return(NULL);
  }

  va_end(ap);
  return(ds_buf(&ds));
}
