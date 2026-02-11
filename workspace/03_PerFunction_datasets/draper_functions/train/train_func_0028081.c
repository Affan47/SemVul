ExpandMonoclinic(int unique_axis, const char *o, char *m)
{
  if (*o) *m++ = *o++;

  switch (tolower(unique_axis))
  {
    case 'a':
      while (*o) *m++ = *o++;
      *m++ = '1';
      *m++ = '1';
      break;
    case 'c':
      *m++ = '1';
      *m++ = '1';
      while (*o) *m++ = *o++;
      break;
    default:
      *m++ = '1';
      while (*o) *m++ = *o++;
      *m++ = '1';
      break;
  }

  *m = '\0';
}
