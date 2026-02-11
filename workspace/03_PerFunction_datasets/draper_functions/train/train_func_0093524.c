cgi_url_unescape (char *value)
{
  int i = 0, o = 0;
  unsigned char *s = (unsigned char *)value;

  if (s == NULL) return value;
  while (s[i])
  {
    if (s[i] == '+')
    {
      s[o++] = ' ';
      i++;
    }
    else if (s[i] == '%' && isxdigit(s[i+1]) && isxdigit(s[i+2]))
    {
      char num;
      num = (s[i+1] >= 'A') ? ((s[i+1] & 0xdf) - 'A') + 10 : (s[i+1] - '0');
      num *= 16;
      num += (s[i+2] >= 'A') ? ((s[i+2] & 0xdf) - 'A') + 10 : (s[i+2] - '0');
      s[o++] = num;
      i+=3;
    }
    else {
      s[o++] = s[i++];
    }
  }
  if (i && o) s[o] = '\0';
  return (char *)s;
}
