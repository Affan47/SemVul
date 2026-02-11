all_digits_p (char const *s)
{
  size_t n = strlen (s);
  return ISDIGIT (s[0]) && n == strspn (s, "0123456789");
}
