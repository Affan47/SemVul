string_appendn (STRING *str, const char *buf, int l)
{
  NEOERR *err;

  err = string_check_length (str, l+1);
  if (err != STATUS_OK) return nerr_pass (err);
  memcpy(str->buf + str->len, buf, l);
  str->len += l;
  str->buf[str->len] = '\0';

  return STATUS_OK;
}
