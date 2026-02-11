ParseArgs(int argc, char **argv) {
  int i;


  for (i = 1; i < argc; i++) {
    const char *arg = argv[i];
    if (strstr(arg, "--debug") == arg) {
      ParseDebugOpt(arg);
      argv[i] = const_cast<char*>("");
    } else if (strcmp(arg, "--version") == 0 || strcmp(arg, "-v") == 0) {
      printf("%s\n", NODE_VERSION);
      exit(0);
    } else if (strcmp(arg, "--vars") == 0) {
#ifdef NODE_PREFIX
      printf("NODE_PREFIX: %s\n", NODE_PREFIX);
#endif
#ifdef NODE_CFLAGS
      printf("NODE_CFLAGS: %s\n", NODE_CFLAGS);
#endif
      exit(0);
    } else if (strstr(arg, "--max-stack-size=") == arg) {
      const char *p = 0;
      p = 1 + strchr(arg, '=');
      max_stack_size = atoi(p);
      argv[i] = const_cast<char*>("");
    } else if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0) {
      PrintHelp();
      exit(0);
    } else if (strcmp(arg, "--eval") == 0 || strcmp(arg, "-e") == 0 ||
        strcmp(arg, "-pe") == 0) {
      if (argc <= i + 1) {
        fprintf(stderr, "Error: --eval requires an argument\n");
        exit(1);
      }
      if (arg[1] == 'p') {
        print_eval = true;
      }
      argv[i] = const_cast<char*>("");
      eval_string = argv[++i];
    } else if (strcmp(arg, "--print") == 0 || strcmp(arg, "-p") == 0) {
      print_eval = true;
      argv[i] = const_cast<char*>("");
    } else if (strcmp(arg, "--v8-options") == 0) {
      argv[i] = const_cast<char*>("--help");
    } else if (argv[i][0] != '-') {
      break;
    }
  }

  option_end_index = i;
}
