classDirectorMethods(Node *n) {
  Node *vtable = Getattr(n, "vtable");

  int len = Len(vtable);
  for (int i = 0; i < len; i++) {
    Node *item = Getitem(vtable, i);
    String *method = Getattr(item, "methodNode");
    String *fqdname = Getattr(item, "fqdname");
    if (GetFlag(method, "feature:nodirector"))
      continue;

    String *type = Getattr(method, "nodeType");
    if (!Cmp(type, "destructor")) {
      classDirectorDestructor(method);
    } else {
      if (classDirectorMethod(method, n, fqdname) == SWIG_OK) {
	Setattr(item, "director", "1");
      }
    }
  }

  return SWIG_OK;
}
