classHandler(Node *n) {
#ifdef CFFI_DEBUG
  Printf(stderr, "class %s::%s\n", "some namespace",
   Getattr(n, "sym:name"));
#endif
  String *name = Getattr(n, "sym:name");
  String *kind = Getattr(n, "kind");


  if (Strcmp(kind, "struct") == 0) {
    emit_struct_union(n, false);
    return SWIG_OK;
  } else if (Strcmp(kind, "union") == 0) {
    emit_struct_union(n, true);
    return SWIG_OK;
  } else if (Strcmp(kind, "class") == 0) {
    emit_class(n);
    Language::classHandler(n);
  } else {
    Printf(stderr, "Don't know how to deal with %s kind of class yet.\n", kind);
    Printf(stderr, " (name: %s)\n", name);
    SWIG_exit(EXIT_FAILURE);
    return SWIG_OK;
  }

  return SWIG_OK;
}
