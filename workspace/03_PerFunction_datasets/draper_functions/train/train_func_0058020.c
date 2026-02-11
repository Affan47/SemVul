get_director_ctor_code(Node *n, String *director_ctor_code, String *director_prot_ctor_code, List *&abstract) {
  String *director_ctor = director_ctor_code;
  int use_director = Swig_directorclass(n);
  if (use_director) {
    Node *pn = Swig_methodclass(n);
    abstract = Getattr(pn, "abstract");
    if (director_prot_ctor_code) {
      int is_notabstract = GetFlag(pn, "feature:notabstract");
      int is_abstract = abstract && !is_notabstract;
      if (is_protected(n) || is_abstract) {
	director_ctor = director_prot_ctor_code;
	Delattr(pn, "abstract");
      } else {
	if (is_notabstract) {
	  Delattr(pn, "abstract");
	} else {
	  abstract = 0;
	}
      }
    }
  }
  return director_ctor;
}
