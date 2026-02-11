tenFiberContextNew(const Nrrd *dtvol) {
  static const char me[]="tenFiberContextNew";
  tenFiberContext *tfx;

  if (!( tfx = _tenFiberContextCommonNew(dtvol, AIR_FALSE,
                                         AIR_NAN, AIR_NAN, AIR_NAN,
                                         tenEstimate1MethodUnknown,
                                         tenEstimate2MethodUnknown) )) {
    biffAddf(TEN, "%s: couldn't create new context", me);
    return NULL;
  }

  return tfx;
}
