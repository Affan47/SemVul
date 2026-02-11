eat_whitespace(const char *s)
{
  tor_assert(s);

  while (1) {
    switch (*s) {
    case '\0':
    default:
      return s;
    case ' ':
    case '\t':
    case '\n':
    case '\r':
      ++s;
      break;
    case '#':
      ++s;
      while (*s && *s != '\n')
        ++s;
    }
  }
}
