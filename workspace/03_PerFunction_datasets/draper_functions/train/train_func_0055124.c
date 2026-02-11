getdata()
{

  long i, j, k, l;
  long idata = 0;

  if (printdata) {
    fprintf(outfile,
       "\nContinuous character contrasts analysis, version %s\n\n",VERSION);
    fprintf(outfile, "%4ld Populations, %4ld Characters\n\n", spp, chars);
    fprintf(outfile, "Name");
    fprintf(outfile, "                       Phenotypes\n");
    fprintf(outfile, "----");
    fprintf(outfile, "                       ----------\n\n");
  }
  x = (phenotype3 **)Malloc((long)spp*sizeof(phenotype3 *));
  cntrast = (phenotype3 **)Malloc((long)spp*sizeof(phenotype3 *));
  ssqcont = (phenotype3 *)Malloc((long)spp*sizeof(phenotype3 *));
  contnum = spp-1;
  for (i = 0; i < spp; i++) {
    initnamefreq(phylofreq, i);
    if (varywithin) {
      sample[i] = phylofreq->Individuals[i];
      contnum += sample[i]-1;
    }
    else sample[i] = 1;
    if (printdata)
      for(j = 0; j < nmlngth; j++)
        putc(nayme[i][j], outfile);
    x[i] = (phenotype3 *)Malloc((long)sample[i]*sizeof(phenotype3));
    cntrast[i] = (phenotype3 *)Malloc((long)(sample[i]*sizeof(phenotype3)));
    ssqcont[i] = (double *)Malloc((long)(sample[i]*sizeof(double)));
    for (k = 0; k <= sample[i]-1; k++) {
      x[i][k] = (phenotype3)Malloc((long)chars*sizeof(double));
      cntrast[i][k] = (phenotype3)Malloc((long)chars*sizeof(double));
      for (j = 1; j <= chars; j++) {
      	x[i][k][j - 1] = phylofreq->Data[idata++];
        if (printdata) {
          fprintf(outfile, "%10.5f", x[i][k][j - 1]);
          if (j % 6 == 0) {
            putc('\n', outfile);
            for (l = 1; l <= nmlngth; l++)
              putc(' ', outfile);
          }
        }
      }
    }
    if (printdata)
      putc('\n', outfile);
  }

  if (printdata)
    putc('\n', outfile);
}
