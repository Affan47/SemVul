increaseSubspaceLimit(int newSize)
{
  if(newSize > maxSubspaceSize) {
    ergo_real *v = new ergo_real[newSize];
    for(int i=0; i<maxSubspaceSize; i++) v[i] = rhsSub[i];
    delete []rhsSub; rhsSub = v;
    LRSolver::increaseSubspaceLimit(newSize);
  }
}
