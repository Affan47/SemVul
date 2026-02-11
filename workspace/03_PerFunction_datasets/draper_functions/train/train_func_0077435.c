main(int argc, char *argv[])
{
  string auxfile = NULL, pattern, inputfile = NULL, dbfile, h;
  string *keys = NULL;
  FILE *f, *db, *aux;
  int c, n;


  prog = argv[0];
  while ((c = getopt(argc, argv, "a:s:n:r:")) != -1) {
    switch (c) {
    case 'a': auxfile = optarg; break;
    case 's': separator = optarg; break;
    case 'n': et_al_limit = atoi(optarg); break;
    case 'r': et_al = optarg; break;
    default: usage();
    }
  }
  if (optind == argc || argc > optind + 2) usage();


  dbfile = argv[optind++];


  if (optind != argc) inputfile = argv[optind];


  if (! auxfile) {
    if (! inputfile) {
      auxfile = "aux.aux";
    } else {
      newarray(auxfile, strlen(argv[optind]) + 5);
      strcpy(auxfile, argv[optind]);
      if ((h = strrchr(auxfile, '.'))) *h = '\0';
      strcat(auxfile, ".aux");
    }
  }


  if (! hcreate(HASHSIZE)) errexit("%s: not enough memory for hash table\n", prog);


  if (! (aux = fopen(auxfile, "r")))
    errexit("%s: %s: %s\n", prog, auxfile, strerror(errno));
  keys = read_keys(aux, &n);
  if (fclose(aux) != 0)
    errexit("%s: %s: %s\n", prog, auxfile, strerror(errno));


  if (! (db = fopen(dbfile, "r")))
    errexit("%s: %s: %s\n", prog, dbfile, strerror(errno));
  read_entries(db, keys, n);
  if (fclose(db) != 0)
    errexit("%s: %s: %s\n", prog, dbfile, strerror(errno));


  if (! (f = inputfile ? fopen(inputfile, "r") : stdin))
    errexit("%s: %s: %s\n", prog, inputfile, strerror(errno));
  pattern = read_pattern(f);
  if (fclose(f) != 0)
    errexit("%s: %s: %s\n", prog, inputfile, strerror(errno));


  copy(pattern, keys, n);

  return 0;
}
