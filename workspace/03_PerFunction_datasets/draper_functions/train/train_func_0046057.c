getalleles()
{
  long i, j, m;

  if (!firstset)
    samenumspfreq(phylofreq, &loci, ith);
  if (contchars ) {
    totalleles = loci;
    for (i = 1; i <= loci; i++) {
      locus[i - 1] = i;
      alleles[i - 1] = 1;
    }
    df = loci;
  } else {
    totalleles = 0;
    if (printdata) {
      fprintf(outfile, "\nNumbers of alleles at the loci:\n");
      fprintf(outfile, "------- -- ------- -- --- -----\n\n");
    }
    for (i = 1; i <= loci; i++) {
      alleles[i-1] = phylofreq->Allele[i-1];
      if (alleles[i - 1] <= 0) {
    printf("ERROR: Bad number of alleles: %ld at locus %ld\n", alleles[i-1], i);
        exxit(-1);
      }
      totalleles += alleles[i - 1];
      if (printdata)
        fprintf(outfile, "%4ld", alleles[i - 1]);
    }
    locus = (long *)Malloc(totalleles*sizeof(long));
    m = 0;
    for (i = 1; i <= loci; i++) {
      for (j = 0; j < alleles[i - 1]; j++)
        locus[m+j] = i;
      m += alleles[i - 1];
    }
    df = totalleles - loci;
  }
  allocview(&curtree, nonodes2, totalleles);
  if (!usertree) {
    allocview(&bestree, nonodes2, totalleles);
    allocview(&priortree, nonodes2, totalleles);
    if (njumble > 1)
      allocview(&bestree2, nonodes2, totalleles);
  }
  for (i = 0; i < spp; i++)
    x[i] = (phenotype3)Malloc(totalleles*sizeof(double));
  pbar = (double *)Malloc(totalleles*sizeof(double));
  if (usertree)
    for (i = 0; i < MAXSHIMOTREES; i++)
      l0gf[i] = (double *)Malloc(totalleles*sizeof(double));
  if (printdata)
    putc('\n', outfile);
}
