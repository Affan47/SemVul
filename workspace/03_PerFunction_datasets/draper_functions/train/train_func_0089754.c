fl_ask(const char *fmt, ...) {

  if (avoidRecursion) return 0;

  va_list ap;

  fl_beep(FL_BEEP_QUESTION);

  va_start(ap, fmt);
  int r = innards(fmt, ap, fl_no, fl_yes, 0);
  va_end(ap);

  return r;
}
