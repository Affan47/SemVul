skip_leading_whitespace (const char *str)
{
  while (*str)
    {
      const char c = *str;
      if (!(c == ' ' || c == '\t'))
	break;
      ++str;
    }
  return str;
}
