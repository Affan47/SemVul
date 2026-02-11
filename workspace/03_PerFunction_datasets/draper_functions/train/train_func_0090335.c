eci_string_clear(eci_string *str)
{
  DBC_CHECK(str);
  str->slen = 0;
  if (str->size == 0)
    eci_string_add(str, 0, NULL, 0);
  else
    str->d[0] = 0;
  DBC_CHECK(str->d[0] == 0);
}
