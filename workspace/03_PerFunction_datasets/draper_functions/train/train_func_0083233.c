allocateLetter(t_Letter *ptLetter, int nSize)
{
  int i = 0;

  ptLetter->nSize  = nSize;
  ptLetter->nTotal = 0;

  ptLetter->anK =(int *) malloc(sizeof(int)*nSize);
  if(!ptLetter->anK)
    goto memoryError;

  ptLetter->anI =(int *) malloc(sizeof(int)*nSize);
  if(!ptLetter->anI)
    goto memoryError;

  ptLetter->adT =(double *) malloc(sizeof(double)*nSize);
  if(!ptLetter->adT)
    goto memoryError;

  for(i = 0; i < nSize; i++){
    ptLetter->anI[i] = 0;
    ptLetter->anK[i] = 0;
    ptLetter->adT[i] = 0.0;
  }

  return;

memoryError:
  fprintf(stderr, "Failed allocating memory in allocateLetter\n");
  fflush(stderr);
  exit(EXIT_FAILURE);
}
