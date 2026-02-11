constantWrapper(Node *n) {

    Swig_require("constantWrapper", n, "*sym:name", "type", "value", NIL);

    String *symname = Getattr(n, "sym:name");
    SwigType *type = Getattr(n, "type");
    String *value = Getattr(n, "value");


    if (SwigType_type(type) == T_MPOINTER) {
      String *wname = Swig_name_wrapper(symname);
      Printf(f_header, "static %s = %s;\n", SwigType_str(type, wname), value);
      value = wname;
    }


    String *tm = Swig_typemap_lookup("constant", n, value, 0);
    if (tm) {
      Replaceall(tm, "$source", value);
      Replaceall(tm, "$target", symname);
      Replaceall(tm, "$symname", symname);
      Replaceall(tm, "$value", value);
      Printf(f_init, "%s\n", tm);
    } else {
      Swig_warning(WARN_TYPEMAP_CONST_UNDEF, input_file, line_number, "Unsupported constant value %s = %s\n", SwigType_str(type, 0), value);
    }

    Swig_restore(n);

    return SWIG_OK;
  }
