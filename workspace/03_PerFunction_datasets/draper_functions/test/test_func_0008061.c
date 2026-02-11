print_char(FILE *f, pcre_uchar *ptr, BOOL utf)
{
pcre_uint32 c = *ptr;

#ifndef SUPPORT_UTF

(void)utf;
if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
else if (c <= 0x80) fprintf(f, "\\x%02x", c);
else fprintf(f, "\\x{%x}", c);
return 0;

#else

#if defined COMPILE_PCRE8

if (!utf || (c & 0xc0) != 0xc0)
  {
  if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
  else if (c < 0x80) fprintf(f, "\\x%02x", c);
  else fprintf(f, "\\x{%02x}", c);
  return 0;
  }
else
  {
  int i;
  int a = PRIV(utf8_table4)[c & 0x3f];
  int s = 6*a;
  c = (c & PRIV(utf8_table3)[a]) << s;
  for (i = 1; i <= a; i++)
    {


    if ((ptr[i] & 0xc0) != 0x80)
      {
      fprintf(f, "\\X{%x}", c);
      return i - 1;
      }


    s -= 6;
    c |= (ptr[i] & 0x3f) << s;
    }
  fprintf(f, "\\x{%x}", c);
  return a;
  }

#elif defined COMPILE_PCRE16

if (!utf || (c & 0xfc00) != 0xd800)
  {
  if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
  else if (c <= 0x80) fprintf(f, "\\x%02x", c);
  else fprintf(f, "\\x{%02x}", c);
  return 0;
  }
else
  {


  if ((ptr[1] & 0xfc00) != 0xdc00)
    {
    fprintf(f, "\\X{%x}", c);
    return 0;
    }

  c = (((c & 0x3ff) << 10) | (ptr[1] & 0x3ff)) + 0x10000;
  fprintf(f, "\\x{%x}", c);
  return 1;
  }

#elif defined COMPILE_PCRE32

if (!utf || (c & 0xfffff800u) != 0xd800u)
  {
  if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
  else if (c <= 0x80) fprintf(f, "\\x%02x", c);
  else fprintf(f, "\\x{%x}", c);
  return 0;
  }
else
  {


  fprintf(f, "\\X{%x}", c);
  return 0;
  }

#endif

#endif
}
