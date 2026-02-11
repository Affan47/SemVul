check_vsprintf (const char *expected, const char *fmt, ...)
{
  int n0, n1, p;
  char buffer[BUF_SIZE];
  va_list ap0, ap1;
  va_start (ap0, fmt);
  va_start (ap1, fmt);

  n0 = mpfr_vsprintf (buffer, fmt, ap0);
  if (strcmp (buffer, expected) != 0)
    {
      printf ("Error in mpfr_vsprintf (s, \"%s\", ...);\n", fmt);
      printf ("expected: \"%s\"\ngot:      \"%s\"\n", expected, buffer);

      va_end (ap0);
      va_end (ap1);
      exit (1);
    }
  va_end (ap0);


  p = (int) (randlimb () % n0);
  if (p == 0 && (randlimb () & 1) == 0)
    {
      n1 = mpfr_vsnprintf (NULL, 0, fmt, ap1);
    }
  else
    {
      buffer[p] = 17;
      n1 = mpfr_vsnprintf (buffer, p, fmt, ap1);
      if (buffer[p] != 17)
        {
          printf ("Buffer overflow in mpfr_vsnprintf for p = %d!\n", p);
          exit (1);
        }
    }
  if (n0 != n1)
    {
      printf ("Error in mpfr_vsnprintf (s, %d, \"%s\", ...) return value\n",
              p, fmt);
      printf ("expected: %d\ngot:      %d\n", n0, n1);

      va_end (ap1);
      exit (1);
    }
  if ((p > 1 && strncmp (expected, buffer, p-1) != 0)
      || (p == 1 && buffer[0] != '\0'))
    {
      char part_expected[BUF_SIZE];
      strncpy (part_expected, expected, p);
      part_expected[p-1] = '\0';
      printf ("Error in mpfr_vsnprintf (s, %d, \"%s\", ...);\n", p, fmt);
      printf ("expected: \"%s\"\ngot:      \"%s\"\n", part_expected, buffer);

      va_end (ap1);
      exit (1);
    }

  va_end (ap1);
  return n0;
}
