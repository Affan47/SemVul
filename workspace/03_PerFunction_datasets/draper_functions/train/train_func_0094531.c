stmwpp_write_double(const double val)
{
  char buff[64];
  char *c;

  c = buff + snprintf(buff, sizeof(buff), "%3.7f", val);
  while (*--c == '0') {
    *c = '\0';
  }
  if (*c == '.') {
    *++c = '0';
  }
  gbfprintf(fout, "%s,", buff);
}
