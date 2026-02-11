umake_file (z, c)
     const char *z;
     int c;
{
  int i;
  FILE *e;

  e = xfopen (z, "w");

  for (i = 0; i < 256; i++)
    {
      int i2;

      for (i2 = 0; i2 < 256; i2++)
	putc (i, e);
    }

  for (i = 0; i < c; i++)
    putc (i, e);

  xfclose (e);
}
