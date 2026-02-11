main(int argc, char *argv[]) {
  int i;

  Preprocessor_define("SWIGCFFI 1", 0);
  SWIG_library_directory("cffi");
  SWIG_config_file("cffi.swg");
  generate_typedef_flag = 0;
  no_swig_lisp = false;
  CWrap = false;
  for (i = 1; i < argc; i++) {
    if (!Strcmp(argv[i], "-help")) {
      Printf(stdout, "cffi Options (available with -cffi)\n");
      Printf(stdout,
       "   -generate-typedef\n"
       "\tIf this option is given then defctype will be used to generate\n"
       "\tshortcuts according to the typedefs in the input.\n"
       "   -[no]cwrap\n"
       "\tTurn on or turn off generation of an intermediate C file when\n"
       "\tcreating a C interface. By default this is only done for C++ code.\n"
       "   -[no]swig-lisp\n"
       "\tTurns on or off generation of code for helper lisp macro, functions,\n"
       "\tetc. which SWIG uses while generating wrappers. These macros, functions\n" "\tmay still be used by generated wrapper code.\n");
    } else if (!strcmp(argv[i], "-cwrap")) {
      CWrap = true;
      Swig_mark_arg(i);
    } else if ((Strcmp(argv[i], "-generate-typedef") == 0)) {
      generate_typedef_flag = 1;
      Swig_mark_arg(i);
    } else if (!strcmp(argv[i], "-nocwrap")) {
      CWrap = false;
      Swig_mark_arg(i);
    } else if (!strcmp(argv[i], "-swig-lisp")) {
      no_swig_lisp = false;
      Swig_mark_arg(i);
    } else if (!strcmp(argv[i], "-noswig-lisp")) {
      no_swig_lisp = true;
      Swig_mark_arg(i);
    }

  }
  f_clhead = NewString("");
  f_clwrap = NewString("");
  f_cl = NewString("");

  allow_overloading();
}
