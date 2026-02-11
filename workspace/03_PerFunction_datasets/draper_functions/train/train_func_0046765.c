find_error_text(int n)
{
const char *s = error_texts;
for (; n > 0; n--)
  {
  while (*s++ != 0) {};
  if (*s == 0) return "Error text not found (please report)";
  }
return s;
}
