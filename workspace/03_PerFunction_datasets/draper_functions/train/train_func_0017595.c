Swig_print_tags(DOH *obj, DOH *root) {
  DOH *croot, *newroot;
  DOH *cobj;

  if (!root)
    croot = NewStringEmpty();
  else
    croot = root;

  while (obj) {
    Printf(stdout, "%s . %s (%s:%d)\n", croot, nodeType(obj), Getfile(obj), Getline(obj));
    cobj = firstChild(obj);
    if (cobj) {
      newroot = NewStringf("%s . %s", croot, nodeType(obj));
      Swig_print_tags(cobj, newroot);
      Delete(newroot);
    }
    obj = nextSibling(obj);
  }
  if (!root)
    Delete(croot);
}
