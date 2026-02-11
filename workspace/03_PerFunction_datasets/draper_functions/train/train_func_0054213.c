main(int margc, char **margv) {
  int i;
  Language *dl = 0;
  ModuleFactory fac = 0;

  int argc;
  char **argv;

  SWIG_merge_envopt(getenv("SWIG_FEATURES"), margc, margv, &argc, &argv);

#ifdef MACSWIG
  SIOUXSettings.asktosaveonclose = false;
  argc = ccommand(&argv);
#endif


  for (i = 0; modules[i].name; i++) {
    Swig_register_module(modules[i].name, modules[i].fac);
  }

  Swig_init_args(argc, argv);


  for (i = 1; i < argc; i++) {
    if (argv[i]) {
      fac = Swig_find_module(argv[i]);
      if (fac) {
	dl = (fac) ();
	Swig_mark_arg(i);
      } else if (strcmp(argv[i], "-nolang") == 0) {
	dl = new Language;
	Swig_mark_arg(i);
      } else if ((strcmp(argv[i], "-dnone") == 0) ||
		 (strcmp(argv[i], "-dhtml") == 0) ||
		 (strcmp(argv[i], "-dlatex") == 0) || (strcmp(argv[i], "-dascii") == 0) || (strcmp(argv[i], "-stat") == 0)) {
	Printf(stderr, "swig: Warning. %s option deprecated.\n", argv[i]);
	Swig_mark_arg(i);
      } else if ((strcmp(argv[i], "-help") == 0) || (strcmp(argv[i], "--help") == 0)) {
	if (strcmp(argv[i], "--help") == 0)
	  strcpy(argv[i], "-help");
	Printf(stdout, "Target Language Options\n");
	for (int j = 0; modules[j].name; j++) {
	  if (modules[j].help) {
	    Printf(stdout, "     %-15s - Generate %s wrappers\n", modules[j].name, modules[j].help);
	  }
	}

      }
    }
  }
  if (!dl) {
    fac = Swig_find_module(SWIG_LANG);
    if (fac) {
      dl = (fac) ();
    }
  }
  int res = SWIG_main(argc, argv, dl);
  delete dl;
  return res;
}
