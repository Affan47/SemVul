nrrdSameSize(const Nrrd *n1, const Nrrd *n2, int useBiff) {
  static const char me[]="nrrdSameSize";
  unsigned int ai;
  char stmp[2][AIR_STRLEN_SMALL];

  if (!(n1 && n2)) {
    biffMaybeAddf(useBiff, NRRD, "%s: got NULL pointer", me);
    return 0;
  }
  if (n1->dim != n2->dim) {
    biffMaybeAddf(useBiff, NRRD, "%s: n1->dim (%u) != n2->dim (%u)",
                  me, n1->dim, n2->dim);
    return 0;
  }
  for (ai=0; ai<n1->dim; ai++) {
    if (n1->axis[ai].size != n2->axis[ai].size) {
      biffMaybeAddf(useBiff, NRRD, "%s: n1->axis[%d].size (%s) "
                    "!= n2->axis[%d].size (%s)", me, ai,
                    airSprintSize_t(stmp[0], n1->axis[ai].size), ai,
                    airSprintSize_t(stmp[1], n2->axis[ai].size));
      return 0;
    }
  }
  return 1;
}
