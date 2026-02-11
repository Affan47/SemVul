restml_pheno_new(long endsite, long sitelength)
{
  phenotype2 ret;
  long k, l;

  endsite++;
  ret = (phenotype2)Malloc(endsite*sizeof(sitelike2));
  for (k = 0; k < endsite; k++) {
    ret[k] = Malloc((sitelength + 1) * sizeof(double));
    for (l = 0; l < sitelength; l++)
      ret[k][l] = 1.0;
  }

  return ret;
}
