pullSysParmSet(pullContext *pctx, int which, double pval) {
  static const char me[]="pullSysParmSet";

  if (!pctx) {
    biffAddf(PULL, "%s: got NULL pointer", me);
    return 1;
  }
  if (!AIR_IN_OP(pullSysParmUnknown, which, pullSysParmLast)) {
    biffAddf(PULL, "%s: sys parm %d not valid", me, which);
    return 1;
  }
  switch(which) {
  case pullSysParmAlpha:
    pctx->sysParm.alpha = pval;
    break;
  case pullSysParmBeta:
    pctx->sysParm.beta = pval;
    break;
  case pullSysParmGamma:
    pctx->sysParm.gamma = pval;
    break;
  case pullSysParmSeparableGammaLearnRescale:
    pctx->sysParm.separableGammaLearnRescale = pval;
    break;
  case pullSysParmTheta:
    pctx->sysParm.theta = pval;
    break;
  case pullSysParmStepInitial:
    pctx->sysParm.stepInitial = pval;
    break;
  case pullSysParmRadiusSpace:
    pctx->sysParm.radiusSpace = pval;
    break;
  case pullSysParmRadiusScale:
    pctx->sysParm.radiusScale = pval;
    break;
  case pullSysParmBinWidthSpace:
    pctx->sysParm.binWidthSpace = pval;
    break;
  case pullSysParmNeighborTrueProb:
    pctx->sysParm.neighborTrueProb = pval;
    break;
  case pullSysParmProbeProb:
    pctx->sysParm.probeProb = pval;
    break;
  case pullSysParmOpporStepScale:
    pctx->sysParm.opporStepScale = pval;
    break;
  case pullSysParmBackStepScale:
    pctx->sysParm.backStepScale = pval;
    break;
  case pullSysParmEnergyDecreasePopCntlMin:
    pctx->sysParm.energyDecreasePopCntlMin = pval;
    break;
  case pullSysParmEnergyDecreaseMin:
    pctx->sysParm.energyDecreaseMin = pval;
    break;
  case pullSysParmConstraintStepMin:
    pctx->sysParm.constraintStepMin = pval;
    break;
  case pullSysParmEnergyIncreasePermit:
    pctx->sysParm.energyIncreasePermit = pval;
    break;
  case pullSysParmFracNeighNixedMax:
    pctx->sysParm.fracNeighNixedMax = pval;
    break;
  case pullSysParmWall:
    pctx->sysParm.wall = pval;
    break;
  default:
    biffAddf(me, "%s: sorry, sys parm %d valid but not handled?", me, which);
    return 1;
  }
  return 0;
}
