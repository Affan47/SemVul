main (int argc, char **argv) {
  int c;
  char *file, *split_spec;

  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
      {"help", 1, 0, 'h'},
      {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "hn:", long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 'h':
      printf ("\
Usage: bsplit [--name <format>] <file> <split-spec>\n");
      break;

    case 'n':
      name = (char*) malloc(strlen(optarg) + 1);
      strcpy(name, optarg);
      break;

    }
  }

  if (! argv[optind]) {
    printf ("Usage: bsplit <file>\n");
    exit (-1);
  } else {
    file = argv[optind++];
    if (! argv[optind]) {
      printf ("Usage: bsplit <file>\n");
      exit (-1);
    } else {
      split_spec = (char*) malloc(strlen(argv[optind]) + 1);
      strcpy(split_spec, argv[optind]);
    }
  }

  bsplit (file, split_spec);

  return (0);
}
