add_parms(ParmList *p, List *patchlist, List *typelist) {
  while (p) {
    SwigType *ty = Getattr(p, "type");
    SwigType *val = Getattr(p, "value");
    Append(typelist, ty);
    Append(typelist, val);
    Append(patchlist, val);
    p = nextSibling(p);
  }
}
