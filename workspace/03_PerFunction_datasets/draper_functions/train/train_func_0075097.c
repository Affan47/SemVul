tor_parse_long(const char *s, int base, long min, long max,
               int *ok, char **next)
{
  char *endptr;
  long r;

  r = strtol(s, &endptr, base);
  CHECK_STRTOX_RESULT();
}
