_nrrdReadNrrdParse_kinds(FILE *file, Nrrd *nrrd,
                         NrrdIoState *nio, int useBiff) {
  static const char me[]="_nrrdReadNrrdParse_kinds";
  unsigned int ai;
  char *info, *tok, *last;
  airArray *mop;

  AIR_UNUSED(file);
  mop = airMopNew();
  info = airStrdup(nio->line + nio->pos);
  airMopAdd(mop, info, airFree, airMopAlways);
  _CHECK_HAVE_DIM;
  for (ai=0; ai<nrrd->dim; ai++) {
    tok = airStrtok(!ai ? info : NULL, _nrrdFieldSep, &last);
    if (!tok) {
      biffMaybeAddf(useBiff, NRRD,
                    "%s: couldn't extract string for kind %d of %d",
                    me, ai+1, nrrd->dim);
      airMopError(mop); return 1;
    }
    if (!strcmp(tok, NRRD_UNKNOWN)) {
      nrrd->axis[ai].kind = nrrdKindUnknown;
      continue;
    }
    if (!strcmp(tok, NRRD_NONE)) {
      nrrd->axis[ai].center = nrrdKindUnknown;
      continue;
    }
    if (!(nrrd->axis[ai].kind = airEnumVal(nrrdKind, tok))) {
      biffMaybeAddf(useBiff, NRRD,
                    "%s: couldn't parse \"%s\" kind %d of %d",
                    me, tok, ai+1, nrrd->dim);
      airMopError(mop); return 1;
    }
  }
  if (airStrtok(!ai ? info : NULL, _nrrdFieldSep, &last)) {
    biffMaybeAddf(useBiff, NRRD,
                  "%s: seem to have more than expected %d kinds",
                  me, nrrd->dim);
    airMopError(mop); return 1;
  }


  airMopOkay(mop);
  return 0;
}
