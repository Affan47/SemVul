main(int argc, char *argv[]) {

    Preprocessor_define("SWIGSEXP 1", 0);

    SWIG_typemap_lang("sexp");
    for (int iX = 0; iX < argc; iX++) {
      if (strcmp(argv[iX], "-typemaplang") == 0) {
	Swig_mark_arg(iX);
	iX++;
	SWIG_typemap_lang(argv[iX]);
	Swig_mark_arg(iX);
	continue;
      }
      if (strcmp(argv[iX], "-help") == 0) {
	fputs(usage, stdout);
      }
    }
  }
