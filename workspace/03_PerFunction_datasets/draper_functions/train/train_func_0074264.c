limnSplineUpdate(limnSpline *spline, Nrrd *_ncpt) {
  static const char me[]="limnSplineUpdate";
  Nrrd *ntmp;
  char stmp[2][AIR_STRLEN_SMALL];

  if (!(spline && _ncpt)) {
    biffAddf(LIMN, "%s: got NULL pointer", me);
    return 1;
  }
  if (nrrdCheck(_ncpt)) {
    biffMovef(LIMN, NRRD, "%s: given nrrd has problems", me);
    return 1;
  }
  if (limnSplineTypeTimeWarp == spline->type) {
    if (!( 1 == _ncpt->dim )) {
      biffAddf(LIMN, "%s: given nrrd has dimension %d, not 1", me, _ncpt->dim);
      return 1;
    }
    if (!( spline->ncpt->axis[2].size == _ncpt->axis[0].size )) {
      biffAddf(LIMN, "%s: have %s time points, but got %s", me,
               airSprintSize_t(stmp[0], spline->ncpt->axis[2].size),
               airSprintSize_t(stmp[1], _ncpt->axis[0].size));
      return 1;
    }
  } else {
    if (!( nrrdSameSize(spline->ncpt, _ncpt, AIR_TRUE) )) {
      biffMovef(LIMN, NRRD, "%s: given ncpt doesn't match original one", me);
      return 1;
    }
  }

  if (limnSplineTypeTimeWarp == spline->type) {
    ntmp = nrrdNew();
    if (nrrdWrap_va(ntmp, spline->time, nrrdTypeDouble, 1,
                    _ncpt->axis[0].size)
        || nrrdConvert(ntmp, _ncpt, nrrdTypeDouble)) {
      biffMovef(LIMN, NRRD, "%s: trouble copying info", me);
      nrrdNix(ntmp); return 1;
    }
    if (_limnSplineTimeWarpSet(spline)) {
      biffAddf(LIMN, "%s: trouble setting time warp", me);
      nrrdNix(ntmp); return 1;
    }
    nrrdNix(ntmp);
  } else {
    if (nrrdConvert(spline->ncpt, _ncpt, nrrdTypeDouble)) {
      biffMovef(LIMN, NRRD, "%s: trouble converting to internal nrrd", me);
      return 1;
    }
  }

  return 0;
}
