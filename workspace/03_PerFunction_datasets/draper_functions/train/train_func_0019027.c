replace_local_types(ParmList *p, const String *name, const String *rep) {
  SwigType *t;
  while (p) {
    t = Getattr(p, "type");
    Replace(t, name, rep, DOH_REPLACE_ANY);
    p = nextSibling(p);
  }
}
