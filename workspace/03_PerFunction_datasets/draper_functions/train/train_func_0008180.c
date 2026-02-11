unrrdu_undosMain(int argc, const char **argv, const char *me,
                 hestParm *hparm) {

  hestOpt *opt = NULL;
  airArray *mop;
  int pret;
  char *err;

  char **name;
  int lenName, ni, reverse, quiet, noAction, mac;

  hestOptAdd(&opt, "r", NULL, airTypeInt, 0, 0, &reverse, NULL,
             "convert back to DOS, instead of converting from DOS to normal");
  hestOptAdd(&opt, "q", NULL, airTypeInt, 0, 0, &quiet, NULL,
             "never print anything to stderr, even for errors.");
  hestOptAdd(&opt, "m", NULL, airTypeInt, 0, 0, &mac, NULL,
             "deal with legacy MAC text files.");
  hestOptAdd(&opt, "n", NULL, airTypeInt, 0, 0, &noAction, NULL,
             "don't actually write converted files, just pretend to. "
             "This is useful to see which files WOULD be converted. ");
  hestOptAdd(&opt, NULL, "file", airTypeString, 1, -1, &name, NULL,
             "all the files to convert.  Each file will be over-written "
             "with its converted contents.  Use \"-\" to read from stdin "
             "and write to stdout", &lenName);

  mop = airMopNew();
  airMopAdd(mop, opt, (airMopper)hestOptFree, airMopAlways);
  USAGE(_unrrdu_undosInfoL);
  PARSE();
  airMopAdd(mop, opt, (airMopper)hestParseFree, airMopAlways);

  for (ni=0; ni<lenName; ni++) {
    undosConvert(me, name[ni], reverse, mac, quiet, noAction);
  }

  airMopOkay(mop);
  return 0;
}
