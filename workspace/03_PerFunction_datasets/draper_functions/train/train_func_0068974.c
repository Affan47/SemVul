_nrrdFieldCheck_kinds(const Nrrd *nrrd, int useBiff) {
  static const char me[]="_nrrdFieldCheck_kinds";
  int val[NRRD_DIM_MAX];
  unsigned int wantLen, ai;

  nrrdAxisInfoGet_nva(nrrd, nrrdAxisInfoKind, val);
  for (ai=0; ai<nrrd->dim; ai++) {
    if (!( nrrdKindUnknown == val[ai]
           || !airEnumValCheck(nrrdKind, val[ai]) )) {
      biffMaybeAddf(useBiff, NRRD,
                    "%s: axis %d kind %d invalid", me, ai, val[ai]);
      return 1;
    }
    wantLen = nrrdKindSize(val[ai]);
    if (wantLen && wantLen != nrrd->axis[ai].size) {
      char stmp[AIR_STRLEN_SMALL];
      biffMaybeAddf(useBiff, NRRD,
                    "%s: axis %d kind %s requires size %u, but have %s", me,
                    ai, airEnumStr(nrrdKind, val[ai]), wantLen,
                    airSprintSize_t(stmp, nrrd->axis[ai].size));
      return 1;
    }
  }
  return 0;
}
