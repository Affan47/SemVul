is_integer(const char *s)
{ if ((*s == '-' || *s == '+') && s[1])
    s++;
  if (!*s || strlen(s) > 20)
    return false;
  while (*s && isdigit(*s))
    s++;
  return *s == '\0';
}
