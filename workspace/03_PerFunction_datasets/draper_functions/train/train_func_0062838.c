destructorHandler(Node *n) {
    Language::destructorHandler(n);
    String *symname = Getattr(n, "sym:name");

    if (proxy_flag) {
      Printv(destructor_call, m3raw_name, ".", Swig_name_destroy(symname), "(swigCPtr)", NIL);
    }
    return SWIG_OK;
  }
