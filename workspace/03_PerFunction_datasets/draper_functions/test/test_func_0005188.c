tend_avgMain(int argc, const char **argv, const char *me,
             hestParm *hparm) {
  int pret;
  hestOpt *hopt = NULL;
  char *perr, *err;
  airArray *mop;

  int ninLen, itype;
  Nrrd **nin, *nout;
  char *outS;

  hestOptAdd(&hopt, "i", "nin1 nin2", airTypeOther, 2, -1, &nin, NULL,
             "list of input diffusion tensor volumes",
             &ninLen, NULL, nrrdHestNrrd);
  hestOptAdd(&hopt, "t", "type", airTypeEnum, 1, 1, &itype, "linear",
             "averaging method",
             NULL, tenInterpType);
  hestOptAdd(&hopt, "o", "nout", airTypeString, 1, 1, &outS, "-",
             "output image (floating point)");

  mop = airMopNew();
  airMopAdd(mop, hopt, (airMopper)hestOptFree, airMopAlways);
  USAGE(_tend_avgInfoL);
  JUSTPARSE();
  airMopAdd(mop, hopt, (airMopper)hestParseFree, airMopAlways);

  nout = nrrdNew();
  airMopAdd(mop, nout, (airMopper)nrrdNuke, airMopAlways);

  if (tenInterpMulti3D(nout, AIR_CAST(const Nrrd*const*, nin), NULL,
                       ninLen, itype, NULL)) {
    airMopAdd(mop, err=biffGetDone(TEN), airFree, airMopAlways);
    fprintf(stderr, "%s: trouble:\n%s\n", me, err);
    airMopError(mop); return 1;
  }

  if (nrrdSave(outS, nout, NULL)) {
    airMopAdd(mop, err=biffGetDone(NRRD), airFree, airMopAlways);
    fprintf(stderr, "%s: trouble writing:\n%s\n", me, err);
    airMopError(mop); return 1;
  }

  airMopOkay(mop);
  return 0;
}
