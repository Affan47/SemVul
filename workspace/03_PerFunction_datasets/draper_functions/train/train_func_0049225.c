tanreadfloat(FILE *fhd, int *lres)
{
  gdouble pouet;
  char buf[100];

  pouet = 1;
  if (*lres==1){
    *lres = fscanf(fhd, "%99s",buf);
    pouet=g_strtod(buf,NULL);
  }

  return pouet;

}
