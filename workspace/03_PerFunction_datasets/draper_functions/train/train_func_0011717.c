SwigType_issubtype(SwigType *t1, SwigType *t2) {
  SwigType *ft1, *ft2;
  String *b1, *b2;
  Hash *h;
  int r = 0;

  if (!subclass)
    return 0;

  ft1 = SwigType_typedef_resolve_all(t1);
  ft2 = SwigType_typedef_resolve_all(t2);
  b1 = SwigType_base(ft1);
  b2 = SwigType_base(ft2);

  h = Getattr(subclass, b2);
  if (h) {
    if (Getattr(h, b1)) {
      r = 1;
    }
  }
  Delete(ft1);
  Delete(ft2);
  Delete(b1);
  Delete(b2);

  return r;
}
