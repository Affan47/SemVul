ParseXLFD(mp, xlfd, lfi)
MemPool mp;
char *xlfd;
HTMLFont lfi;
{
  char *fields[XLFD_COUNT];
  int i;
  char *t;

  t = MPStrDup(mp, xlfd);
  t++;
  fields[0] = t;
  for (i = 1; i < XLFD_COUNT; t++)
  {
    if (*t == '-')
    {
      *t = '\0';
      fields[i++] = t + 1;
    }
  }

  if (strcmp(fields[XLFD_WEIGHT_NAME], "bold") == 0 ||
      strcmp(fields[XLFD_WEIGHT_NAME], "demi") == 0 ||
      strcmp(fields[XLFD_WEIGHT_NAME], "demibold") == 0)
  {
    lfi->weight = 1;
  }
  else lfi->weight = 0;

  lfi->size = atoi(fields[XLFD_PIXEL_SIZE]);

  if (strcmp(fields[XLFD_SLANT], "i") == 0 ||
      strcmp(fields[XLFD_SLANT], "o") == 0)
  {
    lfi->slant = 1;
  }
  else lfi->slant = 0;

  return;
}
