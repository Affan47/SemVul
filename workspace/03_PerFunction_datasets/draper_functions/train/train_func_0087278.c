cgi_puturi(const char *s,
           FILE       *out)
{
  while (*s)
  {
    if (strchr("%@&+ <>#=", *s) || *s < ' ' || *s & 128)
      fprintf(out, "%%%02X", *s & 255);
    else
      putc(*s, out);

    s ++;
  }
}
