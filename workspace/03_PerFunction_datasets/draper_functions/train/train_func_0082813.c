main(int argc, char** argv) {
  g_progname = argv[0];
  kc::setstdiobin();
  if (argc < 2) usage();
  int32_t rv = 0;
  if (!std::strcmp(argv[1], "date")) {
    rv = rundate(argc, argv);
  } else if (!std::strcmp(argv[1], "http")) {
    rv = runhttp(argc, argv);
  } else if (!std::strcmp(argv[1], "rpc")) {
    rv = runrpc(argc, argv);
  } else if (!std::strcmp(argv[1], "ulog")) {
    rv = runulog(argc, argv);
  } else if (!std::strcmp(argv[1], "conf")) {
    rv = runconf(argc, argv);
  } else if (!std::strcmp(argv[1], "version") || !std::strcmp(argv[1], "--version")) {
    printversion();
    rv = 0;
  } else {
    usage();
  }
  return rv;
}
