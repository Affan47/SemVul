dispatching_type(Node *n, Parm *p) {
  String *result = 0;

  String *parsed = Getattr(p, "type");
  String *cl_t = SwigType_typedef_resolve_all(parsed);

  Node *node = NewHash();
  Setattr(node, "type", parsed);
  Setfile(node, Getfile(n));
  Setline(node, Getline(n));
  const String *tm = Swig_typemap_lookup("lispclass", node, Getattr(p, "name"), 0);
  Delete(node);

  if (tm) {
    result = Copy(tm);
  } else {
    String *lookup_type = class_from_class_or_class_ref(parsed);
    if (lookup_type)
      result = lookup_defined_foreign_ltype(lookup_type);
  }


  if (!result)
    result = NewStringf("ff:foreign-pointer");


  Delete(cl_t);
  return result;
}
