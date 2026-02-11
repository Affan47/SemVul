SwigType_inherit(String *derived, String *base, String *cast, String *conversioncode) {
  Hash *h;
  String *dd = 0;
  String *bb = 0;
  if (!subclass)
    subclass = NewHash();


  if (SwigType_istemplate(derived)) {
    String *ty = SwigType_typedef_resolve_all(derived);
    dd = SwigType_typedef_qualified(ty);
    derived = dd;
    Delete(ty);
  }
  if (SwigType_istemplate(base)) {
    String *ty = SwigType_typedef_resolve_all(base);
    bb = SwigType_typedef_qualified(ty);
    base = bb;
    Delete(ty);
  }


  h = Getattr(subclass, base);
  if (!h) {
    h = NewHash();
    Setattr(subclass, base, h);
    Delete(h);
  }
  if (!Getattr(h, derived)) {
    Hash *c = NewHash();
    if (cast)
      Setattr(c, "cast", cast);
    if (conversioncode)
      Setattr(c, "convcode", conversioncode);
    Setattr(h, derived, c);
    Delete(c);
  }

  Delete(dd);
  Delete(bb);
}
