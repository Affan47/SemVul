scan_options(int n,char **in)
{
  char *out;

  if ((out=check_option(in,n,'l','u')) != NULL)
    sscanf(out,"%lu",&(pars.LENGTH));
  if ((out=check_option(in,n,'x','u')) != NULL)
    sscanf(out,"%lu",&EXCLUDE);
  if ((out=check_option(in,n,'c','s')) != NULL) {
    COLUMN=out;
    dimset=1;
  }
  if ((out=check_option(in,n,'m','u')) != NULL)
    sscanf(out,"%u",&(pars.DIM));
  if ((out=check_option(in,n,'F','u')) != NULL)
    sscanf(out,"%u",&WHICHFUTURE);
  if ((out=check_option(in,n,'L','u')) != NULL)
    sscanf(out,"%lu",&FLENGTH);
#if defined(WEIGHTS)
  if ((out=check_option(in,n,'r','f')) != NULL)
    sscanf(out,"%lf",&(pars.maxr));
#endif
  if ((out=check_option(in,n,'k','u')) != NULL)
    sscanf(out,"%u",&(pars.MINN));
  if ((out=check_option(in,n,'N','n')) != NULL)
    nofields=1;
  if ((out=check_option(in,n,'I','u')) != NULL) {
    sscanf(out,"%lu",&seed);
    if (seed == 0)
      seed=(unsigned long)time((time_t*)&seed);
  }
  if ((out=check_option(in,n,'V','u')) != NULL)
    sscanf(out,"%u",&VERBOSITY);
  if ((out=check_option(in,n,'%','f')) != NULL)
    sscanf(out,"%lf",&INNOISE);
  if ((out=check_option(in,n,'o','o')) != NULL)
    if (strlen(out) > 0)
      OUTFILE=out;
}
