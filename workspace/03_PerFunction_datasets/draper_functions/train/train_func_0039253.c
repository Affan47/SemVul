escape(const string s, unsigned char *last)
{
  int i;

  for (i = 0; s[i]; i++)
    switch (s[i]) {
      case '<': printf("&lt;"); break;
      case '>': printf("&gt;"); break;
      case '&': printf("&amp;"); break;
      case '"': printf("&quot;"); break;
      default: putchar(s[i]);
    }
  if (i > 0) *last = s[i-1];
}
