classLookup(SwigType *s) {
  Node *n = 0;


  n = Getattr(classtypes, s);
  if (!n) {
    Symtab *stab = 0;
    SwigType *ty1 = SwigType_typedef_resolve_all(s);
    SwigType *ty2 = SwigType_strip_qualifiers(ty1);
    Delete(ty1);
    ty1 = 0;

    String *base = SwigType_base(ty2);

    Replaceall(base, "class ", "");
    Replaceall(base, "struct ", "");
    Replaceall(base, "union ", "");

    if (strncmp(Char(base), "::", 2) == 0) {
      String *oldbase = base;
      base = NewString(Char(base) + 2);
      Delete(oldbase);
    }

    String *prefix = SwigType_prefix(ty2);


    while (!n) {
      Hash *nstab;
      n = Swig_symbol_clookup(base, stab);
      if (!n)
	break;
      if (Strcmp(nodeType(n), "class") == 0)
	break;
      n = parentNode(n);
      if (!n)
	break;
      nstab = Getattr(n, "sym:symtab");
      n = 0;
      if ((!nstab) || (nstab == stab)) {
	break;
      }
      stab = nstab;
    }
    if (n) {


      if ((Len(prefix) == 0) ||
	  (Strcmp(prefix, "p.") == 0) ||
	  (Strcmp(prefix, "r.") == 0) ||
	  (Strcmp(prefix, "r.p.") == 0) ||
          SwigType_prefix_is_simple_1D_array(prefix)) {
	SwigType *cs = Copy(s);
	Setattr(classtypes, cs, n);
	Delete(cs);
      } else {
	n = 0;
      }
    }
    Delete(ty2);
    Delete(base);
    Delete(prefix);
  }
  if (n && (GetFlag(n, "feature:ignore") || Getattr(n, "feature:onlychildren"))) {
    n = 0;
  }

  return n;
}
