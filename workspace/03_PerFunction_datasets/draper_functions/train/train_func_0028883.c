nrrdResampleTypeOutSet(NrrdResampleContext *rsmc,
                       int type) {
  static const char me[]="nrrdResampleTypeOutSet";

  if (!rsmc) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }
  if (nrrdTypeDefault != type && airEnumValCheck(nrrdType, type)) {
    biffAddf(NRRD, "%s: invalid type %d", me, type);
    return 1;
  }
  if (nrrdTypeBlock == type) {
    biffAddf(NRRD, "%s: can't output %s type", me,
             airEnumStr(nrrdType, nrrdTypeBlock));
    return 1;
  }

  if (rsmc->typeOut != type) {
    rsmc->typeOut = type;
    rsmc->flag[flagTypeOut] = AIR_TRUE;
  }

  return 0;
}
