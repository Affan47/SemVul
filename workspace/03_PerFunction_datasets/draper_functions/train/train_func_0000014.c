gl_puts (buf)
     char *buf;
{
  int len;

  if (buf)
    {
      len = strlen (buf);
      write (1, buf, len);
    }
}
