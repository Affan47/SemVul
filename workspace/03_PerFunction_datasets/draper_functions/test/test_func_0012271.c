Swig_method_call(const_String_or_char_ptr name, ParmList *parms) {
  String *func;
  int i = 0;
  int comma = 0;
  Parm *p = parms;
  SwigType *pt;
  String *nname;

  func = NewString("");
  nname = SwigType_namestr(name);
  Printf(func, "%s(", nname);
  while (p) {
    String *pname;
    pt = Getattr(p, "type");
    if ((SwigType_type(pt) != T_VOID)) {
      if (comma)
	Printf(func, ",");
      pname = Getattr(p, "name");
      Printf(func, "%s", pname);
      comma = 1;
      i++;
    }
    p = nextSibling(p);
  }
  Printf(func, ")");
  return func;
}
