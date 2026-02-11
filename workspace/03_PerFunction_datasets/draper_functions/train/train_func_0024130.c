_tenEstimateEmatUpdate(tenEstimateContext *tec) {
  static const char me[]="tenEstimateEmatUpdate";

  if (tec->flag[flagDwiSet]
      || tec->flag[flagWght]) {

    if (!tec->simulate) {

      if (ell_Nm_pseudo_inv(tec->nemat, tec->nbmat)) {
        biffMovef(TEN, ELL, "%s: trouble pseudo-inverting %ux%u B-matrix", me,
                  AIR_CAST(unsigned int, tec->nbmat->axis[1].size),
                  AIR_CAST(unsigned int, tec->nbmat->axis[0].size));
        return 1;
      }
    }

    tec->flag[flagDwiSet] = AIR_FALSE;
    tec->flag[flagWght] = AIR_FALSE;
  }
  return 0;
}
