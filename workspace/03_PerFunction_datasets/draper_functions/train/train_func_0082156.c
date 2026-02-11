main(int argc, char *argv[]) {
  int i;

  Preprocessor_define("SWIGALLEGROCL 1", 0);
  SWIG_library_directory("allegrocl");
  SWIG_config_file("allegrocl.swg");

  for (i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-identifier-converter")) {
      char *conv = argv[i + 1];

      if (!conv)
	Swig_arg_error();

      Swig_mark_arg(i);
      Swig_mark_arg(i + 1);
      i++;


      if (!strcmp(conv, "lispify")) {
	identifier_converter = "identifier-convert-lispify";
      } else if (!strcmp(conv, "null")) {
	identifier_converter = "identifier-convert-null";
      } else {

	char *idconv = new char[strlen(conv) + 1];
	strcpy(idconv, conv);
	identifier_converter = idconv;
      }
    } else if (!strcmp(argv[i], "-cwrap")) {
      CWrap = true;
      Swig_mark_arg(i);
    } else if (!strcmp(argv[i], "-nocwrap")) {
      CWrap = false;
      Swig_mark_arg(i);
    } else if (!strcmp(argv[i], "-isolate")) {
      unique_swig_package = true;
      Swig_mark_arg(i);
    }

    if (!strcmp(argv[i], "-help")) {
      fprintf(stdout, "Allegro CL Options (available with -allegrocl)\n");
      fprintf(stdout,
	      "    -identifier-converter <type or funcname>\n"
	      "\tSpecifies the type of conversion to do on C identifiers to convert\n"
	      "\tthem to symbols.  There are two built-in converters:  'null' and\n"
	      "\t 'lispify'.  The default is 'null'.  If you supply a name other\n"
	      "\tthan one of the built-ins, then a function by that name will be\n"
	      "\tcalled to convert identifiers to symbols.\n"
	      "\n"
	      "   -[no]cwrap\n"
	      "\tTurn on or turn off generation of an intermediate C file when\n" "\tcreating a C interface. By default this is only done for C++ code.\n"
	      "   -isolate\n"
	      "Define all SWIG helper functions in a package unique to this module. Avoids redefinition warnings when loading multiple SWIGged modules\n"
	      "into the same running Allegro CL image.\n");

    }

  }

  allow_overloading();
}
