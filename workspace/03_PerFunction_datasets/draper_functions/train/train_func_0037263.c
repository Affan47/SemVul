fopen_wplusb_or_die (const char *filename)
{
  FILE  *fp;
  fp = fopen (filename, "w+b");
  if (fp == NULL)
    fp = fopen (filename, "w+");

  if (fp == NULL)
    {
      printf ("Cannot create file %s\n", filename);
      abort ();
    }
  return fp;
}
