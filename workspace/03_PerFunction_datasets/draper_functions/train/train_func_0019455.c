unrrdu_diffMain(int argc, const char **argv, const char *me,
                hestParm *hparm) {
  hestOpt *opt = NULL;
  char *err;
  airArray *mop;
  int pret;

  Nrrd *ninA, *ninB;
  int onlyData, differ;
  double epsilon;
  char explain[AIR_STRLEN_LARGE];

  mop = airMopNew();
  hestOptAdd(&opt, NULL, "ninA", airTypeOther, 1, 1, &ninA, NULL,
             "First input nrrd.",
             NULL, NULL, nrrdHestNrrd);
  hestOptAdd(&opt, NULL, "ninB", airTypeOther, 1, 1, &ninB, NULL,
             "Second input nrrd.",
             NULL, NULL, nrrdHestNrrd);
  hestOptAdd(&opt, "eps,epsilon", "eps", airTypeDouble, 1, 1, &epsilon, "0.0",
             "threshold for allowable difference in values in "
             "data values");
  hestOptAdd(&opt, "od,onlydata", NULL, airTypeInt, 0, 0, &onlyData, NULL,
             "Compare data values only, excluding array meta-data");
  airMopAdd(mop, opt, (airMopper)hestOptFree, airMopAlways);

  USAGE(_unrrdu_diffInfoL);
  PARSE();
  airMopAdd(mop, opt, (airMopper)hestParseFree, airMopAlways);

  if (nrrdCompare(ninA, ninB, onlyData, epsilon, &differ, explain)) {
    airMopAdd(mop, err = biffGetDone(NRRD), airFree, airMopAlways);
    fprintf(stderr, "%s: error doing compare:\n%s", me, err);
    airMopError(mop);
    return 1;
  }
  if (differ) {
    printf("%s: %s differ: %s\n", me, onlyData ? "data values" : "nrrds",
           explain);
  } else {
    if (0 == epsilon) {
      printf("%s: %s are the same\n", me, onlyData ? "data values" : "nrrds");
    } else {
      printf("%s: %s are same or within %g of each other\n", me,
             onlyData ? "data values" : "nrrds", epsilon);
    }
  }

  airMopOkay(mop);
  return 0;
}
