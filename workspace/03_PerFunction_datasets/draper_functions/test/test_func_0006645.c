soggy_test(fc_type fc)
{
  genfile fda3;
  long fsize;

  if (DIAG) {
    char *s;
    s=formal_name(fc,fDA3);
    rprintf("Testing %s for abnormal noun organization....",s);
    rfree(s);
  }
  fda3=openbin(fc,fDA3,"Could not find room file '%s'.",1);
  fsize=binsize(fda3);
  readclose(fda3);

  if (fsize % (maxnoun-300+1)!=0) {
    if (DIAG) rprintf("FOUND!\n");
    return 1;
  }
  if (fsize / (maxnoun-300+1) > 300) {
    if (DIAG) rprintf("FOUND!\n");
    return 1;
  }
  if (DIAG) rprintf("nope.\n");
  return 0;
}
