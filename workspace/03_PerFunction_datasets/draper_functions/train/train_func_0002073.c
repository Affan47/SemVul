readloci()
{
  struct LOC_readloci V;
  long coupling, autosomal;
  double mu;
  int i;

  fscanf(datafile, "%ld%ld%ld%*[^\n]", &nsystem, &risksys, &autosomal);
  getc(datafile);
  if (nsystem > maxlocus)
    inputerror(0L, nsystem, nsystem);
  if (nsystem <= 0)
    inputerror(1L, nsystem, nsystem);
  risk = (risksys != 0);
  sexlink = (autosomal == 1);
  printf("YOU ARE USING LINKAGE (V%s) WITH%3ld-POINT\n", aVersion, nsystem);
  printf("YOU ARE USING FASTLINK (V%s)\n", fVersion);
  if (sexlink)
    printf(" SEXLINKED DATA\n");
  else
    printf(" AUTOSOMAL DATA\n");
  fscanf(datafile, "%ld%lf%lf%ld%*[^\n]", &mutsys, &mu, &mu, &coupling);
  getc(datafile);
  disequi = (coupling == 1);

  fscanf(datafile, "%*[^\n]");
  getc(datafile);
  for (i = 1; i <= nsystem; i++)
    getlocus((long) i, &V);

  if(disequi && ALLELE_SPEED) {

    fprintf(stderr,"\nYou cannot use the disequilibrium model with ALLELE_SPEED set to 1.");
    fprintf(stderr,"\nChange ALLELE_SPEED to 0 in unknown.c and commendefs.h.");
    fprintf(stderr,"\nRecompile unknown  and the main programs.\n");
    exit(EXIT_FAILURE);
  }

  if(disequi && disfreqs) {

    fprintf(stderr,"\nYou cannot use the disequilibrium model with conditional allele frequencies.");
    exit(EXIT_FAILURE);
  }
}
