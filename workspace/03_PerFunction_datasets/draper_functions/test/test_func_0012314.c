pragmaDirective(Node *n) {
    String *lang;
    String *code;
    String *value;
    if (!ImportMode) {
      lang = Getattr(n, "lang");
      code = Getattr(n, "name");
      value = Getattr(n, "value");
      if (Strcmp(lang, "perl5") == 0) {
	if (Strcmp(code, "code") == 0) {

	  if (value) {
	    Printf(pragma_include, "%s\n", value);
	  }
	} else if (Strcmp(code, "include") == 0) {

	  if (value) {
	    FILE *f = Swig_include_open(value);
	    if (!f) {
	      Printf(stderr, "%s : Line %d. Unable to locate file %s\n", input_file, line_number, value);
	    } else {
	      char buffer[4096];
	      while (fgets(buffer, 4095, f)) {
		Printf(pragma_include, "%s", buffer);
	      }
	    }
	    fclose(f);
	  }
	} else {
	  Printf(stderr, "%s : Line %d. Unrecognized pragma.\n", input_file, line_number);
	}
      }
    }
    return Language::pragmaDirective(n);
  }
