runwicked(int argc, char** argv) {
  bool argbrk = false;
  const char* rstr = NULL;
  int32_t thnum = 1;
  int32_t itnum = 1;
  int32_t opts = 0;
  int64_t bnum = -1;
  int64_t capcnt = -1;
  int64_t capsiz = -1;
  bool lv = false;
  for (int32_t i = 2; i < argc; i++) {
    if (!argbrk && argv[i][0] == '-') {
      if (!std::strcmp(argv[i], "--")) {
        argbrk = true;
      } else if (!std::strcmp(argv[i], "-th")) {
        if (++i >= argc) usage();
        thnum = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-it")) {
        if (++i >= argc) usage();
        itnum = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-tc")) {
        opts |= kc::CacheDB::TCOMPRESS;
      } else if (!std::strcmp(argv[i], "-bnum")) {
        if (++i >= argc) usage();
        bnum = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-capcnt")) {
        if (++i >= argc) usage();
        capcnt = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-capsiz")) {
        if (++i >= argc) usage();
        capsiz = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-lv")) {
        lv = true;
      } else {
        usage();
      }
    } else if (!rstr) {
      argbrk = true;
      rstr = argv[i];
    } else {
      usage();
    }
  }
  if (!rstr) usage();
  int64_t rnum = kc::atoix(rstr);
  if (rnum < 1 || thnum < 1 || itnum < 1) usage();
  if (thnum > THREADMAX) thnum = THREADMAX;
  int32_t rv = procwicked(rnum, thnum, itnum, opts, bnum, capcnt, capsiz, lv);
  return rv;
}
