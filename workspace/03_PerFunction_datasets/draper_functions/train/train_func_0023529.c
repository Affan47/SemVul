unix_putenv(value name, value val)
{
  mlsize_t namelen = string_length(name);
  mlsize_t vallen = string_length(val);
  char * s = (char *) caml_stat_alloc(namelen + 1 + vallen + 1);

  memmove (s, String_val(name), namelen);
  s[namelen] = '=';
  memmove (s + namelen + 1, String_val(val), vallen);
  s[namelen + 1 + vallen] = 0;
  if (putenv(s) == -1) {
    caml_stat_free(s);
    uerror("putenv", name);
  }
  return Val_unit;
}
