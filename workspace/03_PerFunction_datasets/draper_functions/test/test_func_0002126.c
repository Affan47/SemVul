tenGradientParmNew(void) {
  tenGradientParm *ret;

  ret = (tenGradientParm *)calloc(1, sizeof(tenGradientParm));
  if (ret) {
    ret->initStep = 1.0;
    ret->jitter = 0.2;
    ret->minVelocity = 0.000000001;
    ret->minPotentialChange = 0.000000001;
    ret->minMean = 0.0001;
    ret->minMeanImprovement = 0.00005;
    ret->single = AIR_FALSE;
    ret->insertZeroVec = AIR_FALSE;
    ret->verbose = 1;
    ret->snap = 0;
    ret->report = 400;
    ret->expo = 1;
    ret->expo_d = 0;
    ret->seed = 42;
    ret->maxEdgeShrink = 20;
    ret->minIteration = 0;
    ret->maxIteration = 1000000;
    ret->step = 0;
    ret->nudge = 0;
    ret->itersUsed = 0;
    ret->potential = 0;
    ret->potentialNorm = 0;
    ret->angle = 0;
    ret->edge = 0;
  }
  return ret;
}
