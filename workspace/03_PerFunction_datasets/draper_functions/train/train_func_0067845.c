tenEstimateBMatricesSet(tenEstimateContext *tec,
                        const Nrrd *nbmat, double bValue, int estimateB0) {
  static const char me[]="tenEstimateBMatricesSet";

  if (!(tec && nbmat)) {
    biffAddf(TEN, "%s: got NULL pointer", me);
    return 1;
  }
  if (!AIR_EXISTS(bValue)) {
    biffAddf(TEN, "%s: given b value doesn't exist", me);
    return 1;
  }
  if (tenBMatrixCheck(nbmat, nrrdTypeDefault, 7)) {
    biffAddf(TEN, "%s: problem with b-matrix list", me);
    return 1;
  }

  tec->bValue = bValue;
  tec->_ngrad = NULL;
  tec->_nbmat = nbmat;
  tec->estimateB0 = estimateB0;

  tec->flag[flagBInfo] = AIR_TRUE;
  return 0;
}
