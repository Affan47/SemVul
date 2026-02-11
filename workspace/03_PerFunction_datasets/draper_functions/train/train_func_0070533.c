destructorDeclaration(Node *n) {

    if (nsname) {
      String *nname = NewStringf("%s::%s", nsname, Getattr(n, "name"));
      Setattr(n, "name", nname);
    }
    return SWIG_OK;
  }
