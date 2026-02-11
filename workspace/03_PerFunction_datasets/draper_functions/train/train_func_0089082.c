concat_width (struct sbuf *buf, char *s, int width)
{
  if (width >= 0)
    {
      char *s1 = xsprintf ("%%.%ds", width);
      char *s2 = xsprintf (s1, s);
      sbuf_concat (buf, s2);
      free (s1);
      free (s2);
    }
  else
    sbuf_concat (buf, s);
}
