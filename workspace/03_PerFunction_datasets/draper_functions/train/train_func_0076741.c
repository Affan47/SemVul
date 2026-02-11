reallocateLetter(t_Letter *ptLetter)
{
  int nM = ptLetter->nM, i = 0;
  int nOldSize = ptLetter->nSize;

  while(ptLetter->nSize < ptLetter->nTotal){
    ptLetter->nSize  *= 2;
  }

  ptLetter->anI = (int *) realloc(ptLetter->anI, sizeof(int)*ptLetter->nSize);
  if(!ptLetter->anI)
    goto memoryError;

  ptLetter->anK = (int *) realloc(ptLetter->anK, sizeof(int)*ptLetter->nSize);
  if(!ptLetter->anK)
    goto memoryError;

  ptLetter->adT = (double *) realloc(ptLetter->adT, sizeof(double)*ptLetter->nSize);
  if(!ptLetter->adT)
    goto memoryError;

  ptLetter->adD = (double *) realloc(ptLetter->adD, sizeof(double)*ptLetter->nSize);
  if(!ptLetter->adD)
    goto memoryError;

  for(i = nOldSize; i < ptLetter->nSize; i++){
    ptLetter->adT[i] = 0.0;
    ptLetter->anK[i] = 0;
    ptLetter->anI[i] = 0;
    ptLetter->adD[i] = 0.0;
  }

  return;

 memoryError:
  fprintf(stderr, "Failed allocating memory in reallocateLetter\n");
  fflush(stderr);
  exit(EXIT_FAILURE);
}
