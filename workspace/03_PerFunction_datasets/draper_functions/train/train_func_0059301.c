distS(int nS, double dFlow)
{
  int nFlow = (int) floor((dFlow + DELTA)/PRECISION);

  if (nS < MAX_S && nFlow < BINS){
    return adLookUp[nS*BINS + nFlow];
  }

  return MAX_DIST;
}
