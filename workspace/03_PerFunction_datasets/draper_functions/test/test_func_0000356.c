constructorDeclaration(Node *n) {
    if (NoExcept) {
      Delattr(n, "throws");
    }

    normalize_parms(Getattr(n, "parms"));
    normalize_parms(Getattr(n, "throws"));


    if (nsname) {
      String *nname = NewStringf("%s::%s", nsname, Getattr(n, "name"));
      Setattr(n, "name", nname);
    }
    clean_overloaded(n);
    return SWIG_OK;
  }
