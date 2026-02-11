ddf_CrissCrossSolve(ddf_LPPtr lp, ddf_ErrorType *err)
{
  switch (lp->objective) {
    case ddf_LPmax:
         ddf_CrissCrossMaximize(lp,err);
      break;

    case ddf_LPmin:
         ddf_CrissCrossMinimize(lp,err);
      break;

    case ddf_LPnone: *err=ddf_NoLPObjective; break;
  }

}
