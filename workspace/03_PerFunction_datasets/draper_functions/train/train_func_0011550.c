main(int argc, char **argv) {
  int32_t i, rv;
  g_progname = argv[0];
  srand(time(NULL));
  if (argc < 2) usage();
  rv = 0;
  if (!strcmp(argv[1], "order")) {
    rv = runorder(argc, argv);
  } else if (!strcmp(argv[1], "index")) {
    rv = runindex(argc, argv);
  } else if (!strcmp(argv[1], "map")) {
    rv = runmap(argc, argv);
  } else if (!strcmp(argv[1], "list")) {
    rv = runlist(argc, argv);
  } else {
    usage();
  }
  if (rv != 0) {
    oprintf("FAILED:");
    for (i = 0; i < argc; i++) {
      oprintf(" %s", argv[i]);
    }
    oprintf("\n\n");
  }
  return rv;
}
