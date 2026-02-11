texinfo_name(Node* n) {
    String *tname = NewString("");
    String *iname = Getattr(n, "sym:name");
    String *wname = Swig_name_wrapper(iname);
    Node* d = Getattr(docs, wname);

    if (is_empty_doc_node(d))
      Printf(tname, "0");
    else
      Printf(tname, "%s_texinfo", wname);

    return tname;
  }
