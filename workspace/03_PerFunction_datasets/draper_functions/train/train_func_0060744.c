parseArgs(const ArgDesc *args, int *argc, char *argv[]) {
  const ArgDesc *arg;
  int i, j;
  GBool ok;

  ok = gTrue;
  i = 1;
  while (i < *argc) {
    if (!strcmp(argv[i], "--")) {
      --*argc;
      for (j = i; j < *argc; ++j)
	argv[j] = argv[j+1];
      break;
    } else if ((arg = findArg(args, argv[i]))) {
      if (!grabArg(arg, i, argc, argv))
	ok = gFalse;
    } else {
      ++i;
    }
  }
  return ok;
}
