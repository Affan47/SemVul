matrix(int nrl,int nrh,int ncl,int nch)

{
  int i, nrow=nrh-nrl+1, ncol=nch-ncl+1;
  float **m;


  m=(float **) malloc((size_t) (nrow+1)*sizeof(float*));
  if (!m) nrerror("allocation failure 1 in matrix()");
  m += 1;
  m -= nrl;


  m[nrl]=(float *) malloc((size_t)((nrow*ncol+1)*sizeof(float)));
  if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
  m[nrl] += 1;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++)
    m[i]=m[i-1]+ncol;

  return(m);
}
