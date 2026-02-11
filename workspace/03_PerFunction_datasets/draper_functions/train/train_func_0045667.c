tenEvecRGBParmCheck(const tenEvecRGBParm *rgbp) {
  static const char me[]="tenEvecRGBParmCheck";

  if (!rgbp) {
    biffAddf(TEN, "%s: got NULL pointer", me);
    return 1;
  }
  if (!( rgbp->which <= 2 )) {
    biffAddf(TEN, "%s: which must be 0, 1, or 2 (not %u)", me, rgbp->which);
    return 1;
  }
  if (airEnumValCheck(tenAniso, rgbp->aniso)) {
    biffAddf(TEN, "%s: anisotropy metric %d not valid", me, rgbp->aniso);
    return 1;
  }
  if (nrrdTypeDefault != rgbp->typeOut
      && airEnumValCheck(nrrdType, rgbp->typeOut)) {
    biffAddf(TEN, "%s: output type (%d) not valid", me, rgbp->typeOut);
    return 1;
  }
  return 0;
}
