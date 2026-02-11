GWEN_Date_fromString(const char *s) {
  int y, m, d;

  if (3==sscanf(s, "%04d%02d%02d", &y, &m, &d)) {
    return GWEN_Date_fromGregorian(y, m, d);
  }
  else {
    DBG_ERROR(GWEN_LOGDOMAIN, "Bad date [%s]", s);
    return NULL;
  }
}
