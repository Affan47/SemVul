lr_next (struct linereader *lr)
{
  int n;

  n = getdelim (&lr->buf, &lr->bufsize, '\n', lr->fp);
  if (n < 0)
    return -1;

  ++lr->lineno;

  if (n > 1 && lr->buf[n - 2] == lr->escape_char && lr->buf[n - 1] == '\n')
    {
#if 0


      --n;
      lr->buf[n - 1] = ' ';
#else
      n -= 2;
#endif
    }

  lr->buf[n] = '\0';
  lr->bufact = n;
  lr->idx = 0;

  return 0;
}
