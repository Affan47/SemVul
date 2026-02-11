parseCmdline(int argc, char **argv)
{
  int i;
  char missingMandatory = 0;

  Program = argv[0];
  cmd.full_cmd_line = catArgv(argc, argv);
  for(i=1, cmd.argc=1; i<argc; i++) {
    if( 0==strcmp("--", argv[i]) ) {
      while( ++i<argc ) argv[cmd.argc++] = argv[i];
      continue;
    }

    if( 0==strcmp("-b", argv[i]) ) {
      int keep = i;
      cmd.numbitsP = 1;
      i = getIntOpt(argc, argv, i, &cmd.numbits, 1);
      cmd.numbitsC = i-keep;
      checkIntLower("-b", &cmd.numbits, cmd.numbitsC, 8);
      checkIntHigher("-b", &cmd.numbits, cmd.numbitsC, 4);
      continue;
    }

    if( 0==strcmp("-o", argv[i]) ) {
      int keep = i;
      cmd.outfileP = 1;
      i = getStringOpt(argc, argv, i, &cmd.outfile, 1);
      cmd.outfileC = i-keep;
      continue;
    }

    if( 0==strcmp("-g", argv[i]) ) {
      int keep = i;
      cmd.numgbP = 1;
      i = getFloatOpt(argc, argv, i, &cmd.numgb, 1);
      cmd.numgbC = i-keep;
      checkFloatLower("-g", &cmd.numgb, cmd.numgbC, 100.0);
      checkFloatHigher("-g", &cmd.numgb, cmd.numgbC, 0.1);
      continue;
    }

    if( argv[i][0]=='-' ) {
      fprintf(stderr, "\n%s: unknown option `%s'\n\n",
              Program, argv[i]);
      usage();
    }
    argv[cmd.argc++] = argv[i];
  }

  if( !cmd.outfileP ) {
    missingErr("-o");
    missingMandatory = 1;
  }
  if( missingMandatory ) exit(EXIT_FAILURE);


  cmd.argv = argv+1;

  cmd.argc -= 1;

  if( 1>cmd.argc ) {
    fprintf(stderr, "%s: there should be at least 1 non-option argument(s)\n",
            Program);
    exit(EXIT_FAILURE);
  }
  if( 100<cmd.argc ) {
    fprintf(stderr, "%s: there should be at most 100 non-option argument(s)\n",
            Program);
    exit(EXIT_FAILURE);
  }
    return &cmd;
}
