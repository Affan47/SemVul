simError(long N, BranchingInfo den) {
  double rn = N*( sumofsquares/double(N)  -  sqr(simBranching(N))) /
    sqr(double(actualCount));
  double rd = den.actualCount>0 ?
    N*( den.sumofsquares/double(N)  -  sqr(den.simBranching(N))) /
    sqr(double(den.actualCount)) : 0.;
  return simBranching(N,den)*sqrt(rn+rd);
}
