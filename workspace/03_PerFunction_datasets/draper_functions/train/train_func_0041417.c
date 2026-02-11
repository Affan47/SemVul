limnSplineCleverNew(Nrrd *ncpt, int info, limnSplineTypeSpec *spec) {
  static const char me[]="limnSplineCleverNew";
  limnSpline *spline;
  Nrrd *ntmp;
  airArray *mop;

  if (!( ncpt && spec )) {
    biffAddf(LIMN, "%s: got NULL pointer", me);
    return NULL;
  }
  mop = airMopNew();
  airMopAdd(mop, ntmp = nrrdNew(), (airMopper)nrrdNuke, airMopAlways);
  if (limnSplineNrrdCleverFix(ntmp, ncpt, info, spec->type)) {
    biffAddf(LIMN, "%s: couldn't fix up given control point nrrd", me);
    airMopError(mop); return NULL;
  }
  if (!( spline = limnSplineNew(ntmp, info, spec) )) {
    biffAddf(LIMN, "%s: couldn't create spline", me);
    airMopError(mop); return NULL;
  }

  airMopOkay(mop);
  return spline;
}
