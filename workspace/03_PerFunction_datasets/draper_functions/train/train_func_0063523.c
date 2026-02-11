nativeWrapper(Node *n) {

    String *name = Getattr(n, "sym:name");
    String *wrapname = Getattr(n, "wrap:name");

    if (!addSymbol(wrapname, n))
      return SWIG_ERROR;

    add_method(name, wrapname, 0);
    return SWIG_OK;
  }
