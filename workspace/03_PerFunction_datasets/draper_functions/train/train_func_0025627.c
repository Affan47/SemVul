nrrdBoundarySpecSprint(char str[AIR_STRLEN_LARGE],
                       const NrrdBoundarySpec *bspec) {
  static const char me[]="nrrdBoundarySpecSprint";
  char *out;

  if (!( str && bspec )) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }
  if (nrrdBoundarySpecCheck(bspec)) {
    biffAddf(NRRD, "%s: problem", me);
    return 1;
  }
  out = str;
  sprintf(out, "%s", airEnumStr(nrrdBoundary, bspec->boundary));
  out += strlen(out);
  if (nrrdBoundaryPad == bspec->boundary) {
    sprintf(out, ":%.17g", bspec->padValue);
  }
  return 0;
}
