getalleles()
{
  long i;

  if (!firstset)
    samenumspfreq(phylofreq, &loci, ith);
  totalleles = 0;
  for (i = 0; i < loci; i++) {
    alleles[i] = phylofreq->Allele[i];
    totalleles += alleles[i];
  }
  df = totalleles - loci;
}
