skip_balanced_braces(const String &text, int p)
{
  const char *s = text.data();
  int len = text.length();
  int brace_level = 0;
  while (p < len) {
    if (s[p] == '{')
      brace_level++;
    else if (s[p] == '}') {
      if (!--brace_level)
	return p + 1;
    }
    p++;
  }
  return p;
}
