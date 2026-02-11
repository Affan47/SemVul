tenEstimateMethodSet(tenEstimateContext *tec, int estimateMethod) {
  static const char me[]="tenEstimateMethodSet";

  if (!tec) {
    biffAddf(TEN, "%s: got NULL pointer", me);
    return 1;
  }
  if (airEnumValCheck(tenEstimate1Method, estimateMethod)) {
    biffAddf(TEN, "%s: estimateMethod %d not a valid %s", me,
            estimateMethod, tenEstimate1Method->name);
    return 1;
  }

  if (tec->estimate1Method != estimateMethod) {
    tec->estimate1Method = estimateMethod;
    tec->flag[flagEstimateMethod] = AIR_TRUE;
  }

  return 0;
}
