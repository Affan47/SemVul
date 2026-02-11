AppendMatchingElementsFromClasses(Tcl_Interp *interp, XOTclClasses *cls,
                                 char *pattern, XOTclObject *matchObject) {
  int rc = 0;

  for ( ; cls; cls = cls->next) {
    XOTclObject *obj = (XOTclObject *)cls->cl;
    if (obj) {
      if (matchObject && obj == matchObject) {


        return 1;
        break;
      } else {
        AppendMatchingElement(interp, obj->cmdName, pattern);
      }
    }
  }
  return rc;
}
