main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must supply a test name to run, choices are:\n");
    for (int i = 0, num = sizeof(tests)/sizeof(unit_test); i < num; i++) {
      printf("  %s\n", tests[i].name);
    }
    return EXIT_FAILURE;
  }

  void *lib = dlopen(getenv(LIB_PRELOAD_ENV_VAR), RTLD_LAZY);
  if (!lib) {
    printf("Failed loading lib: %s\n", dlerror());
    return EXIT_FAILURE;
  }

  void (*init_mocks)() = dlsym(lib, "init_mocks");

  if (!init_mocks) {
    printf("Failed getting mocks init function: %s\n", dlerror());
    return EXIT_FAILURE;
  }
  dlclose(lib);

  init_mocks(&stderred);

  struct sigaction act;
  act.sa_handler = signal_handler;
  sigaction(SIGABRT, &act, NULL);


  dup2(STDOUT_FILENO, STDERR_FILENO);

  for (int i = 0, num = sizeof(tests)/sizeof(unit_test); i < num; i++) {
    if(!strcmp(tests[i].name, argv[1])) {
      stderred.init();
      tests[i].test();
      stderred.reset();
      return EXIT_SUCCESS;
    }
  }

  printf("Test \"%s\" does not exist.\n"
         "Try supplying no arguments to see available tests\n", argv[1]);
  return EXIT_FAILURE;
}
