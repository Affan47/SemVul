main(int argc, const char *argv[]) {

  sys::PrintStackTraceOnErrorSignal();
  PrettyStackTraceProgram X(argc, argv);
  llvm_shutdown_obj Y;

  StringRef ProgName(sys::path::filename(argv[0]));
  if (argc > 1) {
    int (*func)(int, const char *[]) = nullptr;

    if (strcmp(argv[1], "merge") == 0)
      func = merge_main;
    else if (strcmp(argv[1], "show") == 0)
      func = show_main;

    if (func) {
      std::string Invocation(ProgName.str() + " " + argv[1]);
      argv[1] = Invocation.c_str();
      return func(argc - 1, argv + 1);
    }

    if (strcmp(argv[1], "-h") == 0 ||
        strcmp(argv[1], "-help") == 0 ||
        strcmp(argv[1], "--help") == 0) {

      errs() << "OVERVIEW: LLVM profile data tools\n\n"
             << "USAGE: " << ProgName << " <command> [args...]\n"
             << "USAGE: " << ProgName << " <command> -help\n\n"
             << "Available commands: merge, show\n";
      return 0;
    }
  }

  if (argc < 2)
    errs() << ProgName << ": No command specified!\n";
  else
    errs() << ProgName << ": Unknown command!\n";

  errs() << "USAGE: " << ProgName << " <merge|show> [args...]\n";
  return 1;
}
