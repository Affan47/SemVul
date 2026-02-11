saveBatch(unsigned batchLength, real (*coor)[3],
                  real *weight,
		  unsigned nBlocks, int (*shlBlocks)[2],
		  FILE *f) const
{
  pthread_mutex_lock(&fileSaveMutex);

  if(fwrite(&batchLength, sizeof(batchLength), 1, f)!=1            ||
     fwrite(&nBlocks,  sizeof(nBlocks), 1, f) != 1                 ||
     fwrite(shlBlocks, sizeof(int), nBlocks*2, f) != nBlocks*2     ||
     fwrite(coor, sizeof(real), 3*batchLength, f) != 3*batchLength ||
     fwrite(weight, sizeof(real), batchLength, f) != batchLength)
    throw "Cannot save grid point batch on file";


  if(sparsePattern)
    sparsePattern->add(nBlocks, shlBlocks);
  pthread_mutex_unlock(&fileSaveMutex);
  return batchLength;
}
