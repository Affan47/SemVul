fl_password(const char *fmt, const char *defstr, ...) {

  if (avoidRecursion) return 0;


  va_list ap;
  va_start(ap, defstr);
  const char* r = input_innards(fmt, ap, defstr, FL_SECRET_INPUT);
  va_end(ap);
  return r;
}
