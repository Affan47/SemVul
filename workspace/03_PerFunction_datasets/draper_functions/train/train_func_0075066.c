aToL(const String *value) {
    char *endptr;
    long numvalue = strtol(Char(value), &endptr, 0);
    if (*endptr != 0) {
      Swig_warning(WARN_MODULA3_BAD_ENUMERATION, input_file, line_number, "The string <%s> does not denote a numeric value.\n", value);
    }
    return numvalue;
  }
