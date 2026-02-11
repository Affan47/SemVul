runulog(int32_t argc, char** argv) {
  bool argbrk = false;
  const char* path = NULL;
  uint64_t ts = 0;
  bool uw = false;
  bool uf = false;
  for (int32_t i = 2; i < argc; i++) {
    if (!argbrk && argv[i][0] == '-') {
      if (!std::strcmp(argv[i], "--")) {
        argbrk = true;
      } else if (!std::strcmp(argv[i], "-ts")) {
        if (++i >= argc) usage();
        if (!std::strcmp(argv[i], "now") || !std::strcmp(argv[i], "-")) {
          ts = kt::UpdateLogger::clock_pure();
        } else {
          ts = kc::atoix(argv[i]);
        }
      } else if (!std::strcmp(argv[i], "-uw")) {
        uw = true;
      } else if (!std::strcmp(argv[i], "-uf")) {
        uf = true;
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
  int32_t rv = proculog(path, ts, uw, uf);
  return rv;
}
