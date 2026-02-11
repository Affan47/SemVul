convert_intl_marking(const char *str)
{
  static struct astring buf = ASTRING_INIT;
  int len = strlen(str);

  fc_assert_ret_val(len >= 5, str);
  astr_set(&buf, "%s", str + 3);
  *((char *) &astr_str(&buf)[len - 5]) = '\0';

  return Q_(astr_str(&buf));
}
