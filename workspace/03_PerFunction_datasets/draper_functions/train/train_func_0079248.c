tenEstimate1TensorSimulateSingle_f(tenEstimateContext *tec,
                                   float *simval,
                                   float sigma, float bValue, float B0,
                                   const float _ten[7]) {
  static const char me[]="tenEstimate1TensorSimulateSingle_f";
  unsigned int allIdx, dwiIdx;
  double ten[7];

  if (!(tec && simval && _ten)) {
    biffAddf(TEN, "%s: got NULL pointer", me);
    return 1;
  }

  TEN_T_COPY(ten, _ten);
  if (_tenEstimate1TensorSimulateSingle(tec, sigma, bValue, B0, ten)) {
    biffAddf(TEN, "%s: ", me);
    return 1;
  }
  dwiIdx = 0;
  for (allIdx=0; allIdx<tec->allNum; allIdx++) {
    if (tec->estimateB0 || tec->bnorm[allIdx]) {
      simval[allIdx] = AIR_CAST(float, tec->dwiTmp[dwiIdx++]);
    } else {
      simval[allIdx] = B0;
    }
  }
  return 0;
}
