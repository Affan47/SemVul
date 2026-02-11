runcreate(int argc, char** argv) {
  bool argbrk = false;
  const char* path = NULL;
  int32_t oflags = 0;
  int32_t apow = -1;
  int32_t fpow = -1;
  int32_t opts = 0;
  int64_t bnum = -1;
  for (int32_t i = 2; i < argc; i++) {
    if (!argbrk && argv[i][0] == '-') {
      if (!std::strcmp(argv[i], "--")) {
        argbrk = true;
      } else if (!std::strcmp(argv[i], "-otr")) {
        oflags |= kc::HashDB::OTRUNCATE;
      } else if (!std::strcmp(argv[i], "-onl")) {
        oflags |= kc::HashDB::ONOLOCK;
      } else if (!std::strcmp(argv[i], "-otl")) {
        oflags |= kc::HashDB::OTRYLOCK;
      } else if (!std::strcmp(argv[i], "-onr")) {
        oflags |= kc::HashDB::ONOREPAIR;
      } else if (!std::strcmp(argv[i], "-apow")) {
        if (++i >= argc) usage();
        apow = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-fpow")) {
        if (++i >= argc) usage();
        fpow = kc::atoix(argv[i]);
      } else if (!std::strcmp(argv[i], "-ts")) {
        opts |= kc::HashDB::TSMALL;
      } else if (!std::strcmp(argv[i], "-tl")) {
        opts |= kc::HashDB::TLINEAR;
      } else if (!std::strcmp(argv[i], "-tc")) {
        opts |= kc::HashDB::TCOMPRESS;
      } else if (!std::strcmp(argv[i], "-bnum")) {
        if (++i >= argc) usage();
        bnum = kc::atoix(argv[i]);
      } else {
        usage();
      }
    } else if (!path) {
      argbrk = true;
      path = argv[i];
    } else {
      usage();
    }
  }
  if (!path) usage();
  int32_t rv = proccreate(path, oflags, apow, fpow, opts, bnum);
  return rv;
}
