Swig_symbol_template_reduce(SwigType *qt, Symtab *ntab) {
  Parm *p;
  String *templateargs = SwigType_templateargs(qt);
  List *parms = SwigType_parmlist(templateargs);
  Iterator pi = First(parms);
  String *tprefix = SwigType_templateprefix(qt);
  String *tsuffix = SwigType_templatesuffix(qt);
  String *qprefix = SwigType_typedef_qualified(tprefix);
  Append(qprefix, "<(");
  while ((p = pi.item)) {
    String *np;
    String *tp = Swig_symbol_typedef_reduce(p, ntab);
    String *qp = Swig_symbol_type_qualify(tp, ntab);
    Node *n = Swig_symbol_clookup(qp, ntab);
    if (n) {
      String *qual = Swig_symbol_qualified(n);
      np = Copy(Getattr(n, "name"));
      Delete(tp);
      tp = np;
      if (qual && Len(qual)) {
	Insert(np, 0, "::");
	Insert(np, 0, qual);
      }
      Delete(qual);
    } else {
      np = qp;
    }
    Append(qprefix, np);
    pi = Next(pi);
    if (pi.item) {
      Append(qprefix, ",");
    }
    Delete(qp);
    Delete(tp);
  }
  Append(qprefix, ")>");
  Append(qprefix, tsuffix);
  Delete(parms);
  Delete(tprefix);
  Delete(tsuffix);
  Delete(templateargs);
  return qprefix;
}
