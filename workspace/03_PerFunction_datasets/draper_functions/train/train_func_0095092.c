string_append (STRING *str, const char *buf)
{
  NEOERR *err;
  int l;

  l = strlen(buf);
  err = string_check_length (str, l);
  if (err != STATUS_OK) return nerr_pass (err);
  strcpy(str->buf + str->len, buf);
  str->len += l;

  return STATUS_OK;
}
