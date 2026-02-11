Swig_unref_call(Node *n) {
  Node *cn = Swig_methodclass(n);
  String *unref = Swig_rflag_search(cn, "feature:unref", "feature:nounref");
  if (unref) {
    String *pname = Swig_cparm_name(0, 0);
    unref = NewString(unref);
    Replaceall(unref, "$this", pname);
    Replaceall(unref, "$self", pname);
    Delete(pname);
  }
  return unref;
}
