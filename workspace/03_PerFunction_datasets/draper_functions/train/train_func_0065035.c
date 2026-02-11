main(int argc, char *argv[]) {
  int i;

  SWIG_library_directory(chicken_path);


  for (i = 1; i < argc; i++) {
    if (argv[i]) {
      if (strcmp(argv[i], "-help") == 0) {
	fputs(chicken_usage, stdout);
	SWIG_exit(0);
      } else if (strcmp(argv[i], "-proxy") == 0) {
	clos = 1;
	Swig_mark_arg(i);
      } else if (strcmp(argv[i], "-closprefix") == 0) {
	if (argv[i + 1]) {
	  clossymnameprefix = NewString(argv[i + 1]);
	  Swig_mark_arg(i);
	  Swig_mark_arg(i + 1);
	  i++;
	} else {
	  Swig_arg_error();
	}
      } else if (strcmp(argv[i], "-useclassprefix") == 0) {
	useclassprefix = 1;
	Swig_mark_arg(i);
      } else if (strcmp(argv[i], "-unhideprimitive") == 0) {
	hide_primitive = 0;
	Swig_mark_arg(i);
      } else if (strcmp(argv[i], "-nounit") == 0) {
	declare_unit = 0;
	Swig_mark_arg(i);
      } else if (strcmp(argv[i], "-noclosuses") == 0) {
	clos_uses = 0;
	Swig_mark_arg(i);
      } else if (strcmp(argv[i], "-nocollection") == 0) {
	no_collection = 1;
	Swig_mark_arg(i);
      }
    }
  }

  if (!clos)
    hide_primitive = 0;


  Preprocessor_define("SWIGCHICKEN 1", 0);


  SWIG_typemap_lang("chicken");


  SWIG_config_file("chicken.swg");
  allow_overloading();
}
