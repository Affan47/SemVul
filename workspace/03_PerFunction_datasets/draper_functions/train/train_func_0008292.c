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
  if ((out=check_option(in,n,'C','u')) != NULL) {
    sscanf(out,"%u",&compdim);
    compdimset=1;
  }
  if ((out=check_option(in,n,'F','u')) != NULL)
    sscanf(out,"%u",&WHICHFUTURE);
  if ((out=check_option(in,n,'P','s')) != NULL)
    SPART=out;
  if ((out=check_option(in,n,'D','u')) != NULL)
    sscanf(out,"%u",&ODEPTH);
  if ((out=check_option(in,n,'M','u')) != NULL)
    sscanf(out,"%u",&MAXOUT);
  if ((out=check_option(in,n,'s','n')) != NULL)
    scrambleset=1;
  if ((out=check_option(in,n,'V','u')) != NULL)
    sscanf(out,"%u",&VERBOSITY);
  if ((out=check_option(in,n,'o','o')) != NULL)
    if (strlen(out) > 0)
      OUTFILE=out;
}
