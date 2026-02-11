_nrrdReadNrrdParse_labels(FILE *file, Nrrd *nrrd,
                          NrrdIoState *nio, int useBiff) {
  static const char me[]="_nrrdReadNrrdParse_labels";
  char *h;

  unsigned int ai;
  char *info;

  AIR_UNUSED(file);


  info = nio->line + nio->pos;

  _CHECK_HAVE_DIM;
  h = info;
  for (ai=0; ai<nrrd->dim; ai++) {
    if (!( nrrd->axis[ai].label = _nrrdGetQuotedString(&h, useBiff) )) {
      biffMaybeAddf(useBiff, NRRD, "%s: couldn't get get label %d of %d\n",
                    me, ai+1, nrrd->dim);
      return 1;
    }
  }
  if (strlen(h) != strspn(h, _nrrdFieldSep)) {
    biffMaybeAddf(useBiff, NRRD,
                  "%s: seem to have more than expected %d labels",
                  me, nrrd->dim);
    return 1;
  }
  if (_nrrdFieldCheck[nrrdField_labels](nrrd, useBiff)) {
    biffMaybeAddf(useBiff, NRRD, "%s: trouble", me);
    return 1;
  }
  return 0;
}
