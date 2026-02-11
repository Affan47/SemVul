gageOptimSigSet(double *scale, unsigned int num, unsigned int sigmaMax) {
  static const char me[]="gageOptimSigSet";
  unsigned int si;

  if (!scale) {
    biffAddf(GAGE, "%s: got NULL pointer", me);
    return 1;
  }
  if (!AIR_IN_CL(2, num, GAGE_OPTIMSIG_SAMPLES_MAXNUM)) {
    biffAddf(GAGE,
             "%s: requested # sigma samples %u not in known range [2,%u]",
             me, num, GAGE_OPTIMSIG_SAMPLES_MAXNUM);
    return 1;
  }
  if (!AIR_IN_CL(1, sigmaMax, GAGE_OPTIMSIG_SIGMA_MAX)) {
    biffAddf(GAGE, "%s: requested sigma max %u not in known range [1,%u]",
             me, sigmaMax, GAGE_OPTIMSIG_SIGMA_MAX);
    return 1;
  }

  for (si=0; si<num; si++) {
    scale[si] = _optimSigTable[sigmaMax-1][num-2][si];
  }
  return 0;
}
