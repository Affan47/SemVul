unrrdu_hackMain(int argc, const char **argv, const char *me,
                hestParm *hparm) {
  hestOpt *opt = NULL;
  char *out, *err;
  Nrrd *nin, *nout;
  int pret;
  airArray *mop;

  char *what;

  hestOptAdd(&opt, NULL, "what", airTypeString, 1, 1, &what, NULL,
             "what hack to do");
  OPT_ADD_NIN(nin, "input nrrd");
  OPT_ADD_NOUT(out, "output nrrd");

  mop = airMopNew();
  airMopAdd(mop, opt, (airMopper)hestOptFree, airMopAlways);

  USAGE(_unrrdu_hackInfoL);
  PARSE();
  airMopAdd(mop, opt, (airMopper)hestParseFree, airMopAlways);

  nout = nrrdNew();
  airMopAdd(mop, nout, (airMopper)nrrdNuke, airMopAlways);

  if (!strcmp(what, "sdincr")) {
    unsigned int sdim, axi;
    sdim = nin->spaceDim;
    if (!sdim) {
      fprintf(stderr, "%s: need non-zero space dimension", me);
      airMopError(mop);
      return 1;
    }
    if (nrrdCopy(nout, nin)) {
      airMopAdd(mop, err = biffGetDone(NRRD), airFree, airMopAlways);
      fprintf(stderr, "%s: error converting nrrd:\n%s", me, err);
      airMopError(mop);
      return 1;
    }
    nout->spaceDim = sdim + 1;
    nout->space = nrrdSpaceUnknown;
    nout->spaceOrigin[sdim] = 0.0;
    for (axi=0; axi<nout->dim; axi++) {
      if (nrrdSpaceVecExists(sdim, nout->axis[axi].spaceDirection)) {
        nout->axis[axi].spaceDirection[sdim] = 0.0;
      }
    }
  } else {
    fprintf(stderr, "%s: no \"%s\" hack implemented", me, what);
    airMopError(mop);
    return 1;
  }

  SAVE(out, nout, NULL);

  airMopOkay(mop);
  return 0;
}
