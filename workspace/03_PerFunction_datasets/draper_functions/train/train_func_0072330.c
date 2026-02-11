nrrdHistoCheck(const Nrrd *nhist) {
  static const char me[]="nrrdHistoCheck";

  if (!nhist) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }
  if (nrrdTypeBlock == nhist->type) {
    biffAddf(NRRD, "%s: has non-scalar %s type",
             me, airEnumStr(nrrdType, nrrdTypeBlock));
    return 1;
  }
  if (nrrdHasNonExist(nhist)) {
    biffAddf(NRRD, "%s: has non-existent values", me);
    return 1;
  }
  if (1 != nhist->dim) {
    biffAddf(NRRD, "%s: dim == %u != 1",
             me, nhist->dim);
    return 1;
  }
  if (!(nhist->axis[0].size > 1)) {
    biffAddf(NRRD, "%s: has single sample along sole axis", me);
    return 1;
  }

  return 0;
}
