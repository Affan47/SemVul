ddf_RandomPermutation2(ddf_rowindex OV,long t,unsigned int seed)
{
  long k,j,ovj;
  double u,xk,r,rand_max=(double) RAND_MAX;
  int localdebug=ddf_FALSE;

  srand(seed);
  for (j=t; j>1 ; j--) {
    r=rand();
    u=r/rand_max;
    xk=(double)(j*u +1);
    k=(long)xk;
    if (localdebug) fprintf(stderr,"u=%g, k=%ld, r=%g, randmax= %g\n",u,k,r,rand_max);
    ovj=OV[j];
    OV[j]=OV[k];
    OV[k]=ovj;
    if (localdebug) fprintf(stderr,"row %ld is exchanged with %ld\n",j,k);
  }
}
