tend_anscaleMain(int argc, const char **argv, const char *me,
                 hestParm *hparm) {
  int pret;
  hestOpt *hopt = NULL;
  char *perr, *err;
  airArray *mop;

  Nrrd *nin, *nout;
  char *outS;
  float scale;
  int fixDet, makePositive;

  hestOptAdd(&hopt, "s", "scale", airTypeFloat, 1, 1, &scale, NULL,
             "Amount by which to scale deviatoric component of tensor.");
  hestOptAdd(&hopt, "fd", NULL, airTypeInt, 0, 0, &fixDet, NULL,
             "instead of fixing the per-sample trace (the default), fix the "
             "determinant (ellipsoid volume)");
  hestOptAdd(&hopt, "mp", NULL, airTypeInt, 0, 0, &makePositive, NULL,
             "after changing the eigenvalues of the tensor, enforce their "
             "non-negative-ness.  By default, no such constraint is imposed.");
  hestOptAdd(&hopt, "i", "nin", airTypeOther, 1, 1, &nin, "-",
             "input diffusion tensor volume", NULL, NULL, nrrdHestNrrd);
  hestOptAdd(&hopt, "o", "nout", airTypeString, 1, 1, &outS, "-",
             "output image (floating point)");

  mop = airMopNew();
  airMopAdd(mop, hopt, (airMopper)hestOptFree, airMopAlways);
  USAGE(_tend_anscaleInfoL);
  PARSE();
  airMopAdd(mop, hopt, (airMopper)hestParseFree, airMopAlways);

  nout = nrrdNew();
  airMopAdd(mop, nout, (airMopper)nrrdNuke, airMopAlways);
  if (tenAnisoScale(nout, nin, scale, fixDet, makePositive)) {
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
